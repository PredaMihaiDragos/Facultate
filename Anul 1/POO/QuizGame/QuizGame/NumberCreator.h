#pragma once
#include "QuestionCreator.h"

class NumberCreator :
	public QuestionCreator
{
private:
	NumberCreator() {};
	NumberCreator(const NumberCreator&) = delete;
	NumberCreator& operator=(const NumberCreator&) = delete;

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
	static NumberCreator* GetInstance()
	{
		static NumberCreator instance;
		return &instance;
	}
	std::unique_ptr<dbModel> Create() const override;
	std::unique_ptr<Question> Create(const std::string& text) const override;
	std::vector<std::unique_ptr<Question> > LoadAll() const override;
	void ShowCreationDialog(wxWindow* parent, std::function<void(std::shared_ptr<Question>)> createdCallback) const override;
};

