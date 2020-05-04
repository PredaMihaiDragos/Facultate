#include "app.h"

database* app::db = nullptr;

wxIMPLEMENT_APP(app);

bool app::OnInit()
{
    db = database::GetInstance();
    auto questions = LoadQuestions();
    frame = new GameFrame(GameFrameStyle::Window::title, move(questions));
    frame->SetCreatedQuestionCallback(OnQuestionCreated);
    frame->Show(true);
    frame->Destroy();
    return true;
}

int app::OnExit()
{
    return 1;
}

void app::OnQuestionCreated(std::shared_ptr<Question> question)
{
    question->Save();
}

std::vector<std::unique_ptr<Question> > app::LoadQuestions()
{
    std::vector<std::unique_ptr<Question> > ret;
    std::vector<std::unique_ptr<Question> > multipleChoices = MultipleChoiceCreator::GetInstance()->LoadAll();
    std::vector<std::unique_ptr<Question> > numbers = NumberCreator::GetInstance()->LoadAll();
    std::vector<std::unique_ptr<Question> > words = WordCreator::GetInstance()->LoadAll();
    ret.insert(ret.end(), std::make_move_iterator(multipleChoices.begin()), std::make_move_iterator(multipleChoices.end()));
    ret.insert(ret.end(), std::make_move_iterator(numbers.begin()), std::make_move_iterator(numbers.end()));
    ret.insert(ret.end(), std::make_move_iterator(words.begin()), std::make_move_iterator(words.end()));
    return ret;
}