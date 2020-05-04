#include "NumberCreator.h"

NumberCreator* NumberCreator::instance = nullptr;

std::unique_ptr<dbModel> NumberCreator::Create() const
{
    return std::make_unique<Number>();
}

std::unique_ptr<Question> NumberCreator::Create(const std::string& text) const
{
    return std::make_unique<Number>(text);
}

std::vector<std::unique_ptr<Question> > NumberCreator::LoadAll() const
{
    std::vector<std::unique_ptr<Question> > ret;
    const auto con = GetDatabaseCon();
    std::string queryText = "SELECT TEXT,CORRECT FROM " + std::string(Number::tableName);

    try
    {
        SQLite::Statement query(*con, queryText);
        while (query.executeStep())
        {
            std::unique_ptr<Number> current = std::make_unique<Number>(query.getColumn(0));
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
