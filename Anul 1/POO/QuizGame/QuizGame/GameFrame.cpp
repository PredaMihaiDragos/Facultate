#include "GameFrame.h"

enum
{
    ADD_QUESTION = wxID_HIGHEST + 1,
    CREATE_MULTIPLE_CHOICE = wxID_HIGHEST + 2,
    CREATE_WORD = wxID_HIGHEST + 3,
    CREATE_NUMBER = wxID_HIGHEST + 4
};

wxBEGIN_EVENT_TABLE(GameFrame, wxFrame)
EVT_MENU(ADD_QUESTION, GameFrame::OnAddQuestion)
EVT_MENU(CREATE_MULTIPLE_CHOICE, GameFrame::OnCreateQuestion<MultipleChoice>)
EVT_MENU(wxID_EXIT, GameFrame::OnExit)
EVT_MENU(wxID_ABOUT, GameFrame::OnAbout)
wxEND_EVENT_TABLE()


GameFrame::GameFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    CreateMenu();
}

GameFrame::GameFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title)
{
    wxDisplay display(wxDisplay::GetFromWindow(this));
    wxRect screen = display.GetClientArea();
    this->SetPosition(wxPoint(screen.width / 4, screen.height / 4));
    this->SetSize(wxSize(screen.width / 2, screen.height / 2));

    CreateMenu();
}

void GameFrame::CreateMenu()
{
    menuFile = new wxMenu;
    menuFile->Append(ADD_QUESTION, "&Add question\tCtrl-Q",
        "Use this option to add a question to the game.");
    menuFile->AppendSeparator();

    menuFile->Append(wxID_EXIT);
    menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to QuizGame!");
}

void GameFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
    delete menuFile;
    delete menuHelp;
    delete menuBar;
}

void GameFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a QuizGame by Mihai Preda",
        "About QuizGame", wxOK | wxICON_INFORMATION);
}

void GameFrame::OnAddQuestion(wxCommandEvent& event)
{
    wxDialog* dlg = new wxDialog(this, wxID_ANY, "Add question", wxDefaultPosition, wxSize(300, 100));
    wxButton* multipleChoice = new wxButton(dlg, wxID_ANY, "Multiple Choice", wxPoint(10, 10));
    wxButton* word = new wxButton(dlg, wxID_ANY, "Word", wxPoint(120, 10));
    wxButton* number = new wxButton(dlg, wxID_ANY, "Number", wxPoint(200, 10));
    dlg->ShowModal();
}

template<class QuestionType>
void GameFrame::OnCreateQuestion()
{

}