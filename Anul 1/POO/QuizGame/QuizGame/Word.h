#pragma once
#include "Question.h"

class Word : public Question
{
private:
	std::string correct;
public:
	double GetScore();
};

