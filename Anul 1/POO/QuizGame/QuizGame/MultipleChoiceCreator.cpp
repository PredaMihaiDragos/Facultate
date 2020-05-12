#include "MultipleChoiceCreator.h"

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
    catch (Exception &e)
    {
        Logger::GetInstance() += e;
    }
    return ret;
}

void MultipleChoiceCreator::ShowCreationDialog(wxWindow* parent, std::function<void(std::shared_ptr<Question>)> createdCallback) const
{
    auto* dlg = new CreationDialog(parent, createdCallback);
}
