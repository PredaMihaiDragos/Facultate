#include "MultipleChoiceCreator.h"

MultipleChoiceCreator* MultipleChoiceCreator::instance = nullptr;

std::unique_ptr<dbModel> MultipleChoiceCreator::Create() const
{
    return std::make_unique<MultipleChoice>();
}

std::unique_ptr<Question> MultipleChoiceCreator::Create(const std::string& text) const
{
    return std::make_unique<MultipleChoice>(text);
}

std::vector<std::unique_ptr<Question> > MultipleChoiceCreator::LoadAll() const
{
    std::vector<std::unique_ptr<Question> > ret;
    const auto con = GetDatabaseCon();
    std::string queryText = "SELECT TEXT,";
    for (int i = 0; i < MultipleChoice::choices; ++i)
        queryText += "CHOICE" + std::to_string(i) + ",";
    queryText += "CORRECT FROM " + std::string(MultipleChoice::tableName);

    try
    {
        SQLite::Statement query(*con, queryText);
        while (query.executeStep())
        {
            std::unique_ptr<MultipleChoice> current = std::make_unique<MultipleChoice>(query.getColumn(0));
            for (int i = 0; i < MultipleChoice::choices; ++i)
                current->SetChoice(i, query.getColumn(i + 1));
            current->SetCorrect(query.getColumn(MultipleChoice::choices + 1));
            ret.push_back(move(current));
        }
    }
    catch (std::exception& e)
    {
        error << "exception: " << e.what() << std::endl;
    }
    return ret;
}
