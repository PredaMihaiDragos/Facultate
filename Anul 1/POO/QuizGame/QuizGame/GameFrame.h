#pragma once

#include <iostream>
#include <memory>
#include <functional>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/display.h>
#include <wx/dialog.h>

#include "CreateQuestionDialog.h"
#include "questions.h"
#include "error.h"
#include "style.h"

class GameFrame : 
	public wxFrame
{
public:
	GameFrame(const wxString& title, std::vector<std::unique_ptr<Question> > questions = std::vector<std::unique_ptr<Question> >());
	virtual ~GameFrame();
	void SetCreatedQuestionCallback(std::function<void(std::shared_ptr<Question>)> fct) { createdQuestionCallback = fct; }
	void AddQuestion(std::shared_ptr<Question> question);
	void Init();
private:
	GameFrame(const GameFrame& oth) = delete;
	GameFrame& operator=(const GameFrame&) = delete;

	int totalScore;
	wxMenu* menuFile, * menuHelp;
	wxMenuBar* menuBar;
	wxStaticText* questionText;
	int currentQuestion;
	std::vector<std::shared_ptr<Question> > questions;
	std::function<void(std::shared_ptr<Question>)> createdQuestionCallback;
	void CreateMenu();

	void OnAddQuestion(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	void StartGame();
	void UpdateQuestion();
	void UpdateScore();
	void NextQuestion();
	void OnQuestionAnswered(int score, std::string message);
		
	wxDECLARE_EVENT_TABLE();
};

