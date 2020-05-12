#include "app.h"

wxIMPLEMENT_APP(app);

app::~app()
{
}

bool app::OnInit()
{
    std::vector<std::unique_ptr<Question> > questions; 
    std::thread dbThread([&questions]() {
        questions = LoadQuestions();
    });
    frame = new GameFrame(GameFrameStyle::Window::title);
    frame->SetCreatedQuestionCallback(OnQuestionCreated);
    dbThread.join();
    for (auto &q : questions)
        frame->AddQuestion(move(q));
    frame->Init();
    frame->Show(true);
    return true;
}

int app::OnExit()
{
    return 1;
}

void app::OnQuestionCreated(std::shared_ptr<Question> question)
{
    try
    {
        question->Save();
    }
    catch (Exception &e)
    {
        Logger::GetInstance() += e;
    }
}

std::vector<std::unique_ptr<Question> > app::LoadQuestions()
{
    std::vector<std::unique_ptr<Question> > ret;
    std::vector<std::unique_ptr<Question> > multipleChoices = MultipleChoiceCreator::GetInstance().LoadAll();
    std::vector<std::unique_ptr<Question> > numbers = NumberCreator::GetInstance().LoadAll();
    std::vector<std::unique_ptr<Question> > words = WordCreator::GetInstance().LoadAll();
    ret.insert(ret.end(), std::make_move_iterator(multipleChoices.begin()), std::make_move_iterator(multipleChoices.end()));
    ret.insert(ret.end(), std::make_move_iterator(numbers.begin()), std::make_move_iterator(numbers.end()));
    ret.insert(ret.end(), std::make_move_iterator(words.begin()), std::make_move_iterator(words.end()));
    return ret;
}