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


GameFrame::GameFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    CreateMenu();
}

GameFrame::GameFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title)
{
    this->SetPosition(GameFrameStyle::Window::pos);
    this->SetSize(GameFrameStyle::Window::size);

    CreateMenu();
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
    CreateQuestion *dlg = new CreateQuestion(this, QuestionDialogStyle::Window::pos, QuestionDialogStyle::Window::size);
    dlg->Destroy();
}