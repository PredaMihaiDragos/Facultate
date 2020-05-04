#include "WordCreator.h"

WordCreator* WordCreator::instance = nullptr;

std::unique_ptr<dbModel> WordCreator::Create() const
{
    return std::make_unique<Word>();
}


std::unique_ptr<Question> WordCreator::Create(const std::string& text) const
{
    return std::make_unique<Word>(text);
}

std::vector<std::unique_ptr<Question> > WordCreator::LoadAll() const
{
    std::vector<std::unique_ptr<Question> > ret;
    const auto con = GetDatabaseCon();
    std::string queryText = "SELECT TEXT,CORRECT FROM " + std::string(Word::tableName);

    try
    {
        SQLite::Statement query(*con, queryText);
        while (query.executeStep())
        {
            std::unique_ptr<Word> current = std::make_unique<Word>(query.getColumn(0));
            current->SetCorrect(query.getColumn(1));
            ret.push_back(move(current));
        }
    }
    catch (std::exception& e)
    {
        error << "exception: " << e.what() << std::endl;
    }
    return ret;
}

