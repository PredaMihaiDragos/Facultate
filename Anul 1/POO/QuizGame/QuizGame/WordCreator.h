#pragma once
#include "QuestionCreator.h"

class WordCreator :
	public QuestionCreator
{
private:
public:
	std::unique_ptr<Question> CreateQuestion(const std::string& text);
};

