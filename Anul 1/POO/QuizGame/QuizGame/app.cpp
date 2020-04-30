#include "app.h"

wxIMPLEMENT_APP(app);

bool app::OnInit()
{
    frame = new GameFrame(GameFrameStyle::Window::title);
    frame->SetCreatedQuestionCallback(OnQuestionCreated);
    frame->Show(true);
    return true;
}

int app::OnExit()
{
    return 1;
}

void app::OnQuestionCreated(std::shared_ptr<Question> question)
{
    database* db = database::GetInstance();
    db->SaveModel(question);
}

std::vector<std::shared_ptr<Question> > app::LoadQuestions()
{
    database* db = database::GetInstance();
    std::vector<std::shared_ptr<Question> > ret;
    std::vector<std::shared_ptr<MultipleChoice> > multipleChoices = db->LoadTable<MultipleChoice>();
   /* std::vector<std::shared_ptr<Word> > words = db->LoadTable<Word>();
    std::vector<std::shared_ptr<Number> > numbers = db->LoadTable<Number>();
    ret.insert(ret.end(), multipleChoices.begin(), multipleChoices.end());
    ret.insert(ret.end(), words.begin(), words.end());
    ret.insert(ret.end(), numbers.begin(), numbers.end());*/
    return ret;
}