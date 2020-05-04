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
    currentQuestion(0)
{
    this->SetPosition(GameFrameStyle::Window::pos);
    this->SetSize(GameFrameStyle::Window::size);
    this->SetBackgroundColour(GameFrameStyle::Window::colour);
    move(questions.begin(), questions.end(), back_inserter(this->questions));

//    CreateMenu();
//    StartGame();
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
    SetStatusText(GameFrameStyle::Window::status);
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

void GameFrame::AddQuestion(std::shared_ptr<Question> question)
{
    questions.push_back(question);
}

void GameFrame::StartGame()
{
    currentQuestion = 0;
    UpdateQuestion();
}

void GameFrame::UpdateQuestion()
{
    auto current = questions[currentQuestion];
    current->Show(this);
 /*   questionText = new wxStaticText(this, -1, current->GetText(), GameFrameStyle::Question::Text::pos,
                                                                  GameFrameStyle::Question::Text::size,
                                                                  GameFrameStyle::Question::Text::style);
    questionText->SetFont(GameFrameStyle::Question::Text::font);
    if (auto multipleChoice = std::dynamic_pointer_cast<MultipleChoice>(current))
    {
        for (int i = 0; i < MultipleChoice::choices; ++i)
        {
            wxPoint pos = Create::Choice::pos +
                        wxPoint(0, Create::Choice::spaceY * i + Create::Choice::paddingTop);
            wxStaticText* choice = new wxStaticText(this, wxID_ANY, multipleChoice->GetChoice(i), pos, Create::Choice::size, Create::Choice::style);

            long style = Create::Radio::style;
            if (i == 0)
                style |= wxRB_GROUP;
            pos += wxPoint(Create::Choice::size.x + Create::Radio::paddingLeft, 0);
            wxRadioButton* radio = new wxRadioButton(this, wxID_ANY, wxEmptyString, pos, Create::Choice::size, style);
        }
    }
    else if (auto word = std::dynamic_pointer_cast<Word>(current))
    {

    }
    else if (auto number = std::dynamic_pointer_cast<Number>(current))
    {

    }*/
}