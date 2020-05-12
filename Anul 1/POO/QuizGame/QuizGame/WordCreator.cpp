#include "WordCreator.h"

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
    catch (Exception &e)
    {
        Logger::GetInstance() += e;
    }
    return ret;
}

void WordCreator::ShowCreationDialog(wxWindow* parent, std::function<void(std::shared_ptr<Question>)> createdCallback) const
{
    auto* dlg = new CreationDialog(parent, createdCallback);
}