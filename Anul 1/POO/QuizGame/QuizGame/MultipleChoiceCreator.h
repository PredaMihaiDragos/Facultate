#pragma once
#include "QuestionCreator.h"

class MultipleChoiceCreator :
	public QuestionCreator
{
private:
	static MultipleChoiceCreator* instance;
	MultipleChoiceCreator() {};
	MultipleChoiceCreator(const MultipleChoiceCreator&) = delete;
	MultipleChoiceCreator& operator=(const MultipleChoiceCreator&) = delete;
public:
	static MultipleChoiceCreator* GetInstance()
	{
		if (instance == nullptr)
			instance = new MultipleChoiceCreator;
		return instance;
	}
	std::unique_ptr<dbModel> Create() const override;
	std::unique_ptr<Question> Create(const std::string& text) const override;
	std::vector<std::unique_ptr<Question> > LoadAll() const override;
};

