#pragma once
#include "QuestionCreator.h"
#include "QuestionDialogStyle.h"

class WordCreator :
	public QuestionCreator
{
private:
	WordCreator() {};
	WordCreator(const WordCreator&) = delete;
	WordCreator& operator=(const WordCreator&) = delete;

	class CreationDialog
		: public QuestionCreationDialog
	{
	public:
		CreationDialog(wxWindow* parent, std::function<void(std::shared_ptr<Question>)> createdCallback);
	private:
		std::function<void(std::shared_ptr<Question>)> createdCallback;
		wxTextCtrl* inputText;
		wxTextCtrl* inputAnswer;

		void OnSubmitQuestion(wxCommandEvent& event) override;
	};
public:
	static WordCreator* GetInstance()
	{
		static WordCreator instance;
		return &instance;
	}
	std::unique_ptr<dbModel> Create() const override;
	std::unique_ptr<Question> Create(const std::string& text) const override;
	std::vector<std::unique_ptr<Question> > LoadAll() const override;
	void ShowCreationDialog(wxWindow* parent, std::function<void(std::shared_ptr<Question>)> createdCallback) const override;
};

