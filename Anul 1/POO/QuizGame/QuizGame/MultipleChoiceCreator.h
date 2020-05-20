#pragma once
#include "QuestionCreator.h"
#include "QuestionDialogStyle.h"
#include "Singleton.h"

class MultipleChoiceCreator :
	public QuestionCreator,
	public Singleton<MultipleChoiceCreator>
{
public:
	virtual ~MultipleChoiceCreator() {};
	std::unique_ptr<dbModel> Create() const override;
	std::unique_ptr<Question> Create(const std::string& text) const override;
	std::vector<std::unique_ptr<Question> > LoadAll() const override;
	void ShowCreationDialog(wxWindow* parent, std::function<void(std::shared_ptr<Question>)> createdCallback) const override;
private:

	class CreationDialog
		: public QuestionCreationDialog
	{
	public:
		CreationDialog(wxWindow* parent, std::function<void(std::shared_ptr<Question>)> createdCallback);
		~CreationDialog() { }
	private:
		CreationDialog(const CreationDialog& oth) = delete;
		CreationDialog& operator=(const CreationDialog&) = delete;
		std::function<void(std::shared_ptr<Question>)> createdCallback;
		wxTextCtrl* inputText;
		std::vector<wxTextCtrl*> inputChoice;
		std::vector<wxRadioButton*> inputRadio;

		void OnSubmitQuestion(wxCommandEvent& event) override;
	};

	MultipleChoiceCreator() {};
	friend class Singleton<MultipleChoiceCreator>;
};

