#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/display.h>
#include <wx/dialog.h>

#include "questions.h"
#include "creators.h"
#include "error.h"
#include "style.h"

using namespace QuestionDialogStyle;

class CreateQuestionDialog : public wxDialog
{
public:
	CreateQuestionDialog(wxWindow* parent, std::function<void(std::shared_ptr<Question>)> OnQuestionCreated, const wxPoint& pos, const wxSize& size);
	~CreateQuestionDialog();
private:
	void OnExit(wxCommandEvent& event);

	void OnCreateMultipleChoice(wxCommandEvent& event);
	void OnCreateWord(wxCommandEvent& event);
	void OnCreateNumber(wxCommandEvent& event);

	void OnCreateQuestion(const QuestionCreator& creator);

	std::function<void(std::shared_ptr<Question>)> createdCallback;

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