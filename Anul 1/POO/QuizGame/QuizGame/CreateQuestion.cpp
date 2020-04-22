#include "CreateQuestion.h"

enum
{
    CREATE_MULTIPLE_CHOICE = wxID_HIGHEST + 1,
    CREATE_WORD = wxID_HIGHEST + 2,
    CREATE_NUMBER = wxID_HIGHEST + 3,
    SUBMIT_MULTIPLE_CHOICE = wxID_HIGHEST + 4,
    SUBMIT_WORD = wxID_HIGHEST + 5,
    SUBMIT_NUMBER = wxID_HIGHEST + 6
};

wxBEGIN_EVENT_TABLE(CreateQuestion, wxDialog)
EVT_BUTTON(CREATE_MULTIPLE_CHOICE, CreateQuestion::OnCreateMultipleChoice)
EVT_BUTTON(CREATE_WORD, CreateQuestion::OnCreateWord)
EVT_BUTTON(CREATE_NUMBER, CreateQuestion::OnCreateNumber)
EVT_BUTTON(SUBMIT_MULTIPLE_CHOICE, CreateQuestion::OnSubmitMultipleChoice)
EVT_BUTTON(SUBMIT_WORD, CreateQuestion::OnSubmitWord)
EVT_BUTTON(SUBMIT_NUMBER, CreateQuestion::OnSubmitNumber)
wxEND_EVENT_TABLE()

CreateQuestion::CreateQuestion(wxWindow *parent, const wxPoint& pos, const wxSize& size)
    : wxDialog(parent, wxID_ANY, QuestionDialogStyle::Window::title, pos, size)
{
    multipleChoice = new wxButton(this, CREATE_MULTIPLE_CHOICE, QuestionType::MultipleChoice::title, QuestionType::MultipleChoice::pos);
    word = new wxButton(this, CREATE_WORD, QuestionType::Word::title, QuestionType::Word::pos);
    number = new wxButton(this, CREATE_NUMBER, QuestionType::Number::title, QuestionType::Number::pos);

    this->ShowModal();
}

CreateQuestion::~CreateQuestion()
{
    Destroy();

}

void CreateQuestion::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void CreateQuestion::OnCreateMultipleChoice(wxCommandEvent& event)
{
    OnCreateQuestion<MultipleChoice>();
}
void CreateQuestion::OnCreateWord(wxCommandEvent& event)
{
    OnCreateQuestion<Word>();
}
void CreateQuestion::OnCreateNumber(wxCommandEvent& event)
{
    OnCreateQuestion<Number>();
}

template<class T>
void CreateQuestion::OnCreateQuestion()
{
    multipleChoice->Destroy();
    word->Destroy();
    number->Destroy();

    inputText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, Create::Question::pos, Create::Question::size, Create::Question::style);
    inputText->SetHint(Create::Question::hint);

    wxPoint submitPos = Create::Submit::pos + wxPoint(0, Create::Question::spaceY);

    if (std::is_same<T, MultipleChoice>::value)
    {
        for (int i = 0; i < choices; ++i)
        {
            wxPoint pos = Create::Choice::pos + 
                          wxPoint(0, Create::Choice::spaceY * i + Create::Choice::paddingTop);
            wxTextCtrl* choice = new wxTextCtrl(this, wxID_ANY, wxEmptyString, pos, Create::Choice::size, Create::Choice::style);
            choice->SetHint(Create::Choice::hint);

            long style = Create::Radio::style;
            if (i == 0)
                style |= wxRB_GROUP;
            pos += wxPoint(Create::Choice::size.x + Create::Radio::paddingLeft, 0);
            wxRadioButton* radio = new wxRadioButton(this, wxID_ANY, wxEmptyString, pos, Create::Choice::size, style);
            
            inputChoice.push_back(choice);
            inputRadio.push_back(radio);
        }
        submitPos += wxPoint(0, Create::Choice::spaceY * choices);
        submitQuestion = new wxButton(this, SUBMIT_MULTIPLE_CHOICE, Create::Submit::label, submitPos, Create::Submit::size);
    }
    else if(std::is_same<T, Word>::value)
    {
        inputAnswer = new wxTextCtrl(this, wxID_ANY, wxEmptyString, Create::Answer::pos, Create::Answer::size, Create::Answer::style);
        inputAnswer->SetHint(Create::Answer::hint);

        submitPos += wxPoint(0, Create::Answer::spaceY);
        submitQuestion = new wxButton(this, SUBMIT_WORD, Create::Submit::label, submitPos, Create::Submit::size);
    }
    else if (std::is_same<T, Number>::value)
    {
        inputAnswer = new wxTextCtrl(this, wxID_ANY, wxEmptyString, Create::Answer::pos, Create::Answer::size, Create::Answer::style);
        inputAnswer->SetHint(Create::Answer::hint);

        submitPos += wxPoint(0, Create::Answer::spaceY);
        submitQuestion = new wxButton(this, SUBMIT_NUMBER, Create::Submit::label, submitPos, Create::Submit::size);
    }
}

void CreateQuestion::OnSubmitMultipleChoice(wxCommandEvent& event)
{
    
}

void CreateQuestion::OnSubmitWord(wxCommandEvent& event)
{

}

void CreateQuestion::OnSubmitNumber(wxCommandEvent& event)
{

}