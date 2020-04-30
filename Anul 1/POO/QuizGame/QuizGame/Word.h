#pragma once
#include "Question.h"

class Word : public Question
{
private:
public:
	Word(const std::string& _text);
	double GetScore() const override;
	std::unordered_map<std::string, fieldType> toMap() override;
};

