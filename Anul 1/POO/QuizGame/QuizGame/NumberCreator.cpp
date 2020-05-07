#include "NumberCreator.h"

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
    catch (Exception &e)
    {
        Logger::GetInstance() += e;
    }
    return ret;
}

void NumberCreator::ShowCreationDialog(wxWindow* parent, std::function<void(std::shared_ptr<Question>)> createdCallback) const
{
    auto* dlg = new CreationDialog(parent, createdCallback);
}
