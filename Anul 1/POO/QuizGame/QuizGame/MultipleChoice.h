#pragma once

#include "Question.h"

class MultipleChoice : public Question
{
private:
	std::vector<std::string> choice;
	std::string correct;
public:
	double GetScore();
};

