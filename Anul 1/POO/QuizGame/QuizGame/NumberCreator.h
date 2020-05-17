#pragma once
#include "QuestionCreator.h"
#include "Singleton.h"

class NumberCreator :
	public QuestionCreator,
	public Singleton<NumberCreator>
{
public:
	virtual ~NumberCreator() {};
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
		wxTextCtrl* inputAnswer;

		void OnSubmitQuestion(wxCommandEvent& event) override;
	};

	NumberCreator() {};
	friend class Singleton<NumberCreator>;
};


