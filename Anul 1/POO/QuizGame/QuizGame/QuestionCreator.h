#pragma once
#include "questions.h"
#include <memory>

class QuestionCreator
{
private:
public:
	virtual ~QuestionCreator() {};
	virtual std::unique_ptr<Question> CreateQuestion(const std::string& text) = 0;
};