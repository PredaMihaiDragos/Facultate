#pragma once
#include "QuestionCreator.h"

class MultipleChoiceCreator :
	public QuestionCreator
{
public:
	std::unique_ptr<Question> CreateQuestion(const std::string& text);
};

