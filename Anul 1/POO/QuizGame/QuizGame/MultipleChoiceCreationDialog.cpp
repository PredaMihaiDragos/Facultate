#include "MultipleChoiceCreator.h"

MultipleChoiceCreator::CreationDialog::CreationDialog(wxWindow* parent, std::function<void(std::shared_ptr<Question>)> createdCallback) :
    QuestionCreationDialog(parent),
    createdCallback(createdCallback)
{
	using namespace QuestionDialogStyle;

	inputText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, Create::Question::pos, Create::Question::size, Create::Question::style);
    inputText->SetHint(Create::Question::hint);


    for (int i = 0; i < MultipleChoice::choices; ++i)
    {
        wxPoint pos = Create::Choice::pos +
            wxPoint(0, Create::Choice::spaceY * i + Create::Choice::paddingTop);
        wxTextCtrl* choice = new wxTextCtrl(this, wxID_ANY, wxEmptyString, pos, Create::Choice::size, Create::Choice::style);
        choice->SetHint(Create::Choice::hint);

        long style = Create::Radio::style;
        if (i == 0)
            style |= wxRB_GROUP;
        pos += wxPoint(Create::Choice::size.x + Create::Radio::paddingLeft, Create::Radio::paddingTop);
        wxRadioButton* radio = new wxRadioButton(this, wxID_ANY, wxEmptyString, pos, wxDefaultSize, style);

        inputChoice.push_back(choice);
        inputRadio.push_back(radio);
    }
    wxPoint submitPos = Create::Submit::pos + wxPoint(0, Create::Choice::pos.y + Create::Choice::spaceY * MultipleChoice::choices);
    SetSubmitPos(submitPos);

	this->ShowModal();
}

void MultipleChoiceCreator::CreationDialog::OnSubmitQuestion(wxCommandEvent& event)
{
    std::string text = inputText->GetValue().ToStdString();
    auto questionToCreate = std::make_shared<MultipleChoice>(text);
    std::vector<std::string> choiceText;
    assert(inputChoice.size() == MultipleChoice::choices && inputRadio.size() == MultipleChoice::choices);
    for (int i = 0; i < MultipleChoice::choices; ++i)
    {
        std::string inputValue = inputChoice[i]->GetValue().ToStdString();
        (*questionToCreate)[i] = inputValue;
        if (inputRadio[i]->GetValue())
            questionToCreate->SetCorrect(inputValue);
    }
    try
    {
        if (createdCallback == nullptr)
            throw Exception("Error creating question: Question created callback not set!", "MultipleChoiceCreationDialog.cpp");
        else
            createdCallback(questionToCreate);
    }
    catch (Exception &e)
    {
        Logger::GetInstance() += e;
    }
    this->EndModal(0); 
}