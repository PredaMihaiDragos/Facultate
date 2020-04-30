#include "CreateQuestionDialog.h"

enum
{
    CREATE_MULTIPLE_CHOICE = wxID_HIGHEST + 1,
    CREATE_WORD = wxID_HIGHEST + 2,
    CREATE_NUMBER = wxID_HIGHEST + 3,
    SUBMIT_QUESTION = wxID_HIGHEST + 4,
};

wxBEGIN_EVENT_TABLE(CreateQuestionDialog, wxDialog)
EVT_BUTTON(CREATE_MULTIPLE_CHOICE, CreateQuestionDialog::OnCreateMultipleChoice)
EVT_BUTTON(CREATE_WORD, CreateQuestionDialog::OnCreateWord)
EVT_BUTTON(CREATE_NUMBER, CreateQuestionDialog::OnCreateNumber)
EVT_BUTTON(SUBMIT_QUESTION, CreateQuestionDialog::OnSubmitQuestion)
wxEND_EVENT_TABLE()

CreateQuestionDialog::CreateQuestionDialog(wxWindow* parent, std::function<void(std::shared_ptr<Question>)> OnQuestionCreated, const wxPoint& pos, const wxSize& size) :
    wxDialog(parent, wxID_ANY, QuestionDialogStyle::Window::title, pos, size),
    createdCallback(OnQuestionCreated),
    inputText(nullptr),
    inputAnswer(nullptr),
    submitQuestion(nullptr),
    multipleChoice(new wxButton(this, CREATE_MULTIPLE_CHOICE, QuestionType::MultipleChoice::title, QuestionType::MultipleChoice::pos)),
    word(new wxButton(this, CREATE_WORD, QuestionType::Word::title, QuestionType::Word::pos)),
    number(new wxButton(this, CREATE_NUMBER, QuestionType::Number::title, QuestionType::Number::pos))
{
    this->ShowModal();
}

CreateQuestionDialog::~CreateQuestionDialog()
{
    Destroy();
}

void CreateQuestionDialog::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void CreateQuestionDialog::OnCreateMultipleChoice(wxCommandEvent& event)
{
    OnCreateQuestion<MultipleChoice>();
}
void CreateQuestionDialog::OnCreateWord(wxCommandEvent& event)
{
    OnCreateQuestion<Word>();
}
void CreateQuestionDialog::OnCreateNumber(wxCommandEvent& event)
{
    OnCreateQuestion<Number>();
}

template<class T>
void CreateQuestionDialog::OnCreateQuestion()
{
    multipleChoice->Destroy();
    word->Destroy();
    number->Destroy();

    inputText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, Create::Question::pos, Create::Question::size, Create::Question::style);
    inputText->SetHint(Create::Question::hint);

    wxPoint submitPos = Create::Submit::pos + wxPoint(0, Create::Question::spaceY);

    if (std::is_same<T, MultipleChoice>::value)
    {
        creator = std::make_unique<MultipleChoiceCreator>();
        for (int i = 0; i < MultipleChoice::choices; ++i)
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
        submitPos += wxPoint(0, Create::Choice::spaceY * MultipleChoice::choices);
    }
    else if(std::is_same<T, Word>::value)
    {
        creator = std::make_unique<WordCreator>();
        inputAnswer = new wxTextCtrl(this, wxID_ANY, wxEmptyString, Create::Answer::pos, Create::Answer::size, Create::Answer::style);
        inputAnswer->SetHint(Create::Answer::hint);

        submitPos += wxPoint(0, Create::Answer::spaceY);
    }
    else if (std::is_same<T, Number>::value)
    {
        creator = std::make_unique<NumberCreator>();
        inputAnswer = new wxTextCtrl(this, wxID_ANY, wxEmptyString, Create::Answer::pos, Create::Answer::size, Create::Answer::style);
        inputAnswer->SetHint(Create::Answer::hint);

        submitPos += wxPoint(0, Create::Answer::spaceY);
    }
    submitQuestion = new wxButton(this, SUBMIT_QUESTION, Create::Submit::label, submitPos, Create::Submit::size);
}

void CreateQuestionDialog::OnSubmitQuestion(wxCommandEvent& event)
{
    std::string text = inputText->GetValue().ToStdString();
    std::shared_ptr<Question> questionToCreate = creator->CreateQuestion(text);
    
    if (std::shared_ptr<MultipleChoice> multipleChoiceToCreate = std::dynamic_pointer_cast<MultipleChoice>(questionToCreate))
    {
        std::vector<std::string> choiceText;
        assert(inputChoice.size() == MultipleChoice::choices && inputRadio.size() == MultipleChoice::choices);
        for (int i = 0; i < MultipleChoice::choices; ++i)
        {
            std::string inputValue = inputChoice[i]->GetValue().ToStdString();
            multipleChoiceToCreate->SetChoice(i, inputValue);
            if (inputRadio[i]->GetValue())
                questionToCreate->SetCorrect(inputValue);
        }
    }
    else
    {
        assert(inputAnswer != nullptr);
        questionToCreate->SetCorrect(inputAnswer->GetValue().ToStdString());
    }
    if (createdCallback == nullptr)
        throw "Error creating question: Question created callback not set!";
    else
        createdCallback(questionToCreate);
    this->EndModal(0);
}