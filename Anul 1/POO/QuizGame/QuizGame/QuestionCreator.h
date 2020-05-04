#pragma once
#include "questions.h"

#include "dbModelCreator.h"

class QuestionCreator : public dbModelCreator
{
private:
public:
	virtual ~QuestionCreator() {};
	virtual std::unique_ptr<Question> Create(const std::string& text) const = 0;
	virtual std::vector<std::unique_ptr<Question> > LoadAll() const = 0;
};