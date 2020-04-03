#include "dbf.h"

inline bool isValidChar(unsigned char x)
{
    return x != ' ' && (isdigit(x) || isalpha(x));
}

string trim(const string& str)
{
    string ret;
    int start = 0, end = str.size() - 1;
    while (start <= end && !isValidChar(str[start]))
        start++;
    while (start <= end && !isValidChar(str[end]))
        end--;
    while (start <= end)
        ret += str[start++];
    return ret;
}

string toString(const char* str, int length)
{
    string ret;
    for (int i = 0; i < length; i++)
        ret += str[i];
    return ret;
}

dbf::dbf(const char* flink)
{
    unsigned char buffer[32];
    link = fopen(flink, "rb");
    fread(buffer, 32, 1, link);
    nRecords = (uint)buffer[4] + (uint)buffer[5] * 256 +
        (uint)buffer[6] * 256 * 256 + (uint)buffer[7] * 256 * 256 * 256;
    rStart = (uint)buffer[8] + (uint)buffer[9] * 256;
    rSize = (uint)buffer[10] + (uint)buffer[11] * 256;
    nFields = (rStart - 264) / 32 - 1;

    //    cout << "Records: " << nRecords << "\nStart: " << rStart << "\nrSize: " << 
    //       rSize << "\nFields: " << nFields << endl;

    for (int i = 0; i < nFields; ++i)
    {
        fseek(link, 32 + 32 * i, SEEK_SET);
        fread(buffer, 32, 1, link);
        string t;
        for (int i = 0; i < 10; i++)
            t += buffer[i];
        fieldName.push_back(trim(t));
        fieldSize.push_back((uint)buffer[16]);
        fieldPos.push_back((uint)buffer[12] + (uint)buffer[13] * 256 +
            (uint)buffer[14] * 256 * 256 + (uint)buffer[15] * 256 * 256 * 256);
    //    cout << fieldName.back() << " " << fieldSize.back() << " " << fieldPos.back() << "\n";
    }
}

dbf::~dbf()
{
    fclose(link);
}

int dbf::getFieldID(const string& name)
{
    for (int i = 0; i < nFields; ++i)
    {
       if (fieldName[i] == name)
            return i;
    }
    return -1;
}

int dbf::getRecord(const string& fieldName, const string &fieldValue)
{
    int nameID = getFieldID(fieldName);
    char deleted[2];
    assert(nameID != -1);
    char* buffer = new char[fieldSize[nameID]];
    for (int i = rStart; i < nRecords * rSize; i += rSize)
    {
        fseek(link, i, SEEK_SET);
        fread(deleted, 2, 1, link);
        if (deleted[0] == '*')
            continue;
        fseek(link, i + fieldPos[nameID], SEEK_SET);
        fread(buffer, fieldSize[nameID], 1, link);
        if (trim(toString(buffer, fieldSize[nameID])) == fieldValue)
        {
            delete[] buffer;
            return (i - rStart) / rSize;
        }
    }
    delete[] buffer;
    return -1;
}

vector<int> dbf::getMultipleRecords(const string& fieldName, const string& fieldValue)
{
    vector<int> ret;
    char deleted[2], buffer[32];
    for (int i = rStart; i < nRecords * rSize; i += rSize)
    {
        fseek(link, i, SEEK_SET);
        fread(deleted, 2, 1, link);
        if (deleted[0] == '*')
            continue;
        if (fieldName.size() != 0 && fieldValue.size() != 0)
        {
            int nameID = getFieldID(fieldName);
            fseek(link, i + fieldPos[nameID], SEEK_SET);
            fread(buffer, fieldSize[nameID], 1, link);
        }
        if ((fieldName.size() == 0 || (fieldValue.size() == 0)) || trim(toString(buffer, 32)) == fieldValue)
            ret.push_back((i - rStart) / rSize);
    }
    return ret;
}

string dbf::getField(int rID, const string& fName)
{
    int fieldID = getFieldID(fName);
    char * buffer = new char[fieldSize[fieldID]];
    int pos = rStart + rID * rSize + fieldPos[fieldID];
    fseek(link, pos, SEEK_SET);
    fread(buffer, fieldSize[fieldID], 1, link);
    string ret(trim(toString(buffer, fieldSize[fieldID])));
    delete[] buffer;
    return ret;
}