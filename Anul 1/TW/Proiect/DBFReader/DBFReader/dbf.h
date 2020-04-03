#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

typedef unsigned int uint;

class dbf
{
private:
    FILE* link;
    uint nRecords, rStart, rSize, nFields;
    vector<string> fieldName;
    vector<uint> fieldSize, fieldPos;
    int getFieldID(const string&);
public:
    dbf(const string& str) : dbf(str.c_str()) {};
    dbf(const char*);
    ~dbf();
    int getRecord(const string&, const string&);
    //if empty fieldName and fieldValue -> returns all recrods
    vector<int> getMultipleRecords(const string& fieldName = "", const string& fieldValue = "");
    string getField(int, const string&);
};

