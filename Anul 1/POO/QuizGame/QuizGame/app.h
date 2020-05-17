#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <thread>

#include "GameFrame.h"
#include "Question.h"
#include "Logger.h"

class app : 
    public wxApp
{
public:
    bool OnInit();
    int OnExit();
    app() {};
    virtual ~app();
    static void OnQuestionCreated(std::shared_ptr<Question> question);
    static std::vector<std::unique_ptr<Question> > LoadQuestions();
private:
    GameFrame* frame;
    app(const app& oth) = delete;
    app& operator=(const app&) = delete;
};

