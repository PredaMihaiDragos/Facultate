#pragma once
#include "QuestionCreator.h"

class NumberCreator :
	public QuestionCreator
{
private:
	static NumberCreator* instance;
	NumberCreator() {};
	NumberCreator(const NumberCreator&) = delete;
	NumberCreator& operator=(const NumberCreator&) = delete;
public:
	static NumberCreator* GetInstance()
	{
		if (instance == nullptr)
			instance = new NumberCreator;
		return instance;
	}
	std::unique_ptr<dbModel> Create() const override;
	std::unique_ptr<Question> Create(const std::string& text) const override;
	std::vector<std::unique_ptr<Question> > LoadAll() const override;
};

