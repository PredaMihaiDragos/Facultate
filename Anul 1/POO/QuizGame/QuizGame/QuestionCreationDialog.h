#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/display.h>
#include <wx/dialog.h>

#include "Question.h"
#include "style.h"

class QuestionCreationDialog :
	public wxDialog
{
public:
	QuestionCreationDialog(wxWindow* parent);
	virtual ~QuestionCreationDialog() {};
protected:
	void SetSubmitPos(const wxPoint& pos) { submitQuestion->SetPosition(pos); }
private:
	QuestionCreationDialog(const QuestionCreationDialog& oth) = delete;
	QuestionCreationDialog& operator=(const QuestionCreationDialog&) = delete;
	wxButton* submitQuestion;
	virtual void OnSubmitQuestion(wxCommandEvent& event) = 0;

	wxDECLARE_EVENT_TABLE();
};

