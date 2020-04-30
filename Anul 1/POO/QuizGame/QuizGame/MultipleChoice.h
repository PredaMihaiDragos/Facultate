#pragma once

#include "Question.h"

class MultipleChoice : public virtual Question
{

public:
	static const int choices = 4;
	MultipleChoice(const std::string &_text);
	double GetScore() const override;
	std::unordered_map<std::string, fieldType> toMap() override;
	void SetChoice(int index, const std::string& str);

private:
	std::vector<std::string> choice;
};

