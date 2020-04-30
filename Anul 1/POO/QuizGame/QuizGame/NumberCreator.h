#pragma once
#include "QuestionCreator.h"

class NumberCreator :
	public QuestionCreator
{
private:
public:
	std::unique_ptr<Question> CreateQuestion(const std::string& text);
};

