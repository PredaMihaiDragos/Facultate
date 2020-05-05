#pragma once
#include "QuestionCreator.h"
#include "QuestionDialogStyle.h"

class MultipleChoiceCreator :
	public QuestionCreator
{
private:
	MultipleChoiceCreator() {};
	MultipleChoiceCreator(const MultipleChoiceCreator&) = delete;
	MultipleChoiceCreator& operator=(const MultipleChoiceCreator&) = delete;

	class CreationDialog
		: public QuestionCreationDialog
	{
	public:
		CreationDialog(wxWindow* parent, std::function<void(std::shared_ptr<Question>)> createdCallback);
	private:
		std::function<void(std::shared_ptr<Question>)> createdCallback;
		wxTextCtrl* inputText;
		std::vector<wxTextCtrl*> inputChoice;
		std::vector<wxRadioButton*> inputRadio;

		void OnSubmitQuestion(wxCommandEvent& event) override;
	};
public:
	static MultipleChoiceCreator* GetInstance()
	{
		static MultipleChoiceCreator instance;
		return &instance;
	}
	std::unique_ptr<dbModel> Create() const override;
	std::unique_ptr<Question> Create(const std::string& text) const override;
	std::vector<std::unique_ptr<Question> > LoadAll() const override;
	void ShowCreationDialog(wxWindow* parent, std::function<void(std::shared_ptr<Question>)> createdCallback) const override;
};

