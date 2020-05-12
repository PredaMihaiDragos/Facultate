#include "GameFrame.h"

enum
{
    ADD_QUESTION = wxID_HIGHEST + 1,
};

wxBEGIN_EVENT_TABLE(GameFrame, wxFrame)
EVT_MENU(ADD_QUESTION, GameFrame::OnAddQuestion)
EVT_MENU(wxID_EXIT, GameFrame::OnExit)
EVT_MENU(wxID_ABOUT, GameFrame::OnAbout)
wxEND_EVENT_TABLE()


GameFrame::GameFrame(const wxString& title, std::vector<std::unique_ptr<Question> > questions) : 
    wxFrame(NULL, wxID_ANY, title),
    currentQuestion(0),
    totalScore(0.0)
{
    this->SetPosition(GameFrameStyle::Window::pos);
    this->SetSize(GameFrameStyle::Window::size);
    this->SetBackgroundColour(GameFrameStyle::Window::colour);
    move(questions.begin(), questions.end(), back_inserter(this->questions));
}

void GameFrame::Init()
{
    CreateMenu();
    StartGame();
}

void GameFrame::CreateMenu()
{
    menuFile = new wxMenu;
    menuFile->Append(ADD_QUESTION, GameFrameStyle::Menu::File::addQuestion);
    menuFile->AppendSeparator();

    menuFile->Append(wxID_EXIT);
    menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
}

void GameFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void GameFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(GameFrameStyle::Menu::Help::aboutMessage,
        GameFrameStyle::Menu::Help::aboutTitle, wxOK | wxICON_INFORMATION);
}

void GameFrame::OnAddQuestion(wxCommandEvent& event)
{
    CreateQuestionDialog *dlg = new CreateQuestionDialog(this, createdQuestionCallback, QuestionDialogStyle::Window::pos, QuestionDialogStyle::Window::size);
    dlg->Destroy();
}

GameFrame::~GameFrame()
{
    Destroy();
}

void GameFrame::AddQuestion(std::shared_ptr<Question> question)
{
    questions.push_back(question);
}

void GameFrame::StartGame()
{
    currentQuestion = 0;
    totalScore = 0;
    UpdateQuestion();
    UpdateScore();
}

void GameFrame::UpdateQuestion()
{
    auto current = questions[currentQuestion];
    (*current)(this, [this](int score, std::string message) {
        this->OnQuestionAnswered(score, message);
    });
}

void GameFrame::NextQuestion()
{
    currentQuestion++;
    if (currentQuestion >= questions.size())
    {
        wxMessageBox("The game ended! Your total score was " + std::to_string(totalScore) + ". Press OK to start again.", "Game Over", wxOK);
        StartGame();
    }
    else
        UpdateQuestion();
}

void GameFrame::OnQuestionAnswered(int score, std::string message)
{
    wxMessageBox(message, "Answer result", wxOK);
    totalScore += score;
    UpdateScore();
    NextQuestion();
}

void GameFrame::UpdateScore()
{
    SetStatusText(GameFrameStyle::Window::scoreMessage + std::to_string(totalScore));
}