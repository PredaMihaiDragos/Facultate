#include "WordCreator.h"

WordCreator::CreationDialog::CreationDialog(wxWindow* parent, std::function<void(std::shared_ptr<Question>)> createdCallback) :
    QuestionCreationDialog(parent),
    createdCallback(createdCallback)
{
    using namespace QuestionDialogStyle;

    inputText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, Create::Question::pos, Create::Question::size, Create::Question::style);
    inputText->SetHint(Create::Question::hint);
    inputAnswer = new wxTextCtrl(this, wxID_ANY, wxEmptyString, Create::Answer::pos, Create::Answer::size, Create::Answer::style);
    inputAnswer->SetHint(Create::Answer::hint);

    wxPoint submitPos = Create::Submit::pos + wxPoint(0, Create::Answer::pos.y + Create::Answer::size.y);
    SetSubmitPos(submitPos);

    this->ShowModal();
}

void WordCreator::CreationDialog::OnSubmitQuestion(wxCommandEvent& event)
{
    std::string text = inputText->GetValue().ToStdString();
    auto questionToCreate = std::make_shared<Word>(text);
    questionToCreate->SetCorrect(inputAnswer->GetValue().ToStdString());
    try
    {
        if (createdCallback == nullptr)
            throw Exception("Error creating question: Question created callback not set!", "WordCreationDialog.cpp");
        else
            createdCallback(questionToCreate);
    }
    catch (Exception &e)
    {
        Logger::GetInstance() += e;
    }
    this->EndModal(0);
}