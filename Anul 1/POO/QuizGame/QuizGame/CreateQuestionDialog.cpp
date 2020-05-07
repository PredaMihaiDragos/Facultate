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
    OnCreateQuestion(MultipleChoiceCreator::GetInstance());
}
void CreateQuestionDialog::OnCreateWord(wxCommandEvent& event)
{
    OnCreateQuestion(WordCreator::GetInstance());
}
void CreateQuestionDialog::OnCreateNumber(wxCommandEvent& event)
{
    OnCreateQuestion(NumberCreator::GetInstance());
}

void CreateQuestionDialog::OnCreateQuestion(const QuestionCreator& creator)
{
    this->EndModal(0);
    creator.ShowCreationDialog(this->GetParent(), createdCallback);
}