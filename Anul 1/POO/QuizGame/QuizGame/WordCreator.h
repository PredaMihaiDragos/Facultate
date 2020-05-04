#pragma once
#include "QuestionCreator.h"

class WordCreator :
	public QuestionCreator
{
private:
	static WordCreator* instance;
	WordCreator() {};
	WordCreator(const WordCreator&) = delete;
	WordCreator& operator=(const WordCreator&) = delete;
public:
	static WordCreator* GetInstance()
	{
		if (instance == nullptr)
			instance = new WordCreator;
		return instance;
	}
	std::unique_ptr<dbModel> Create() const override;
	std::unique_ptr<Question> Create(const std::string& text) const override;
	std::vector<std::unique_ptr<Question> > LoadAll() const override;
};

