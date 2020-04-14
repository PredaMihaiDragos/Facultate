#pragma once

#include "Question.h"

class MultipleChoice : public Question
{
private:
	std::vector<std::string> choice;
public:
	double GetScore();
};

