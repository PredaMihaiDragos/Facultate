#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/display.h>
#include <wx/dialog.h>

#include "questions.h"
#include "error.h"
#include "style.h"

using namespace QuestionDialogStyle;

class CreateQuestion : public wxDialog
{
public:
	CreateQuestion(wxWindow* parent, const wxPoint& pos, const wxSize& size);
	~CreateQuestion();
private:
	void OnExit(wxCommandEvent& event);

	void OnCreateMultipleChoice(wxCommandEvent& event);
	void OnCreateWord(wxCommandEvent& event);
	void OnCreateNumber(wxCommandEvent& event);
	void OnSubmitMultipleChoice(wxCommandEvent& event);
	void OnSubmitWord(wxCommandEvent& event);
	void OnSubmitNumber(wxCommandEvent& event);

	template<class T>
	void OnCreateQuestion();

	wxButton* multipleChoice;
	wxButton* word;
	wxButton* number;

	wxTextCtrl* inputText;
	std::vector<wxTextCtrl*> inputChoice;
	std::vector<wxRadioButton*> inputRadio;
	wxTextCtrl* inputAnswer;
	wxButton* submitQuestion;

	wxDECLARE_EVENT_TABLE();
};