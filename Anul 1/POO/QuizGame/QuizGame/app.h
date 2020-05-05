#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "GameFrame.h"
#include "Question.h"

class app : 
    public wxApp
{
private:
    GameFrame* frame;
public:
    bool OnInit();
    int OnExit();
    static void OnQuestionCreated(std::shared_ptr<Question> question);
    static std::vector<std::unique_ptr<Question> > LoadQuestions();
};

