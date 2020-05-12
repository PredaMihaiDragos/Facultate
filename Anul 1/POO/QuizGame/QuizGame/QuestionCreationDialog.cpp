#include "QuestionCreationDialog.h"

enum
{
    SUBMIT_QUESTION = wxID_HIGHEST + 1,
};

wxBEGIN_EVENT_TABLE(QuestionCreationDialog, wxDialog)
EVT_BUTTON(SUBMIT_QUESTION, QuestionCreationDialog::OnSubmitQuestion)
wxEND_EVENT_TABLE()

QuestionCreationDialog::QuestionCreationDialog(wxWindow* parent) :
	wxDialog(parent, wxID_ANY, QuestionDialogStyle::Window::title, QuestionDialogStyle::Window::pos, QuestionDialogStyle::Window::size)
{
	submitQuestion = new wxButton(this, SUBMIT_QUESTION, QuestionDialogStyle::Create::Submit::label, wxDefaultPosition, QuestionDialogStyle::Create::Submit::size);
}