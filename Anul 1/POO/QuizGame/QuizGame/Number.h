#pragma once

#include "Question.h"

class Number : public virtual Question
{
private:
public:
	Number(const std::string& _text);
	double GetScore() const override;
	std::unordered_map<std::string, fieldType> toMap() override;
};

