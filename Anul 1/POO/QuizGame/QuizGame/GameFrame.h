#pragma once

#include <iostream>
#include <memory>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/display.h>
#include <wx/dialog.h>

#include "CreateQuestion.h"
#include "questions.h"
#include "error.h"
#include "style.h"

class GameFrame : public wxFrame
{
public:
    GameFrame(const wxString& title);
    GameFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    wxMenu *menuFile, *menuHelp;
    wxMenuBar *menuBar;
    void CreateMenu();

    void OnAddQuestion(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

