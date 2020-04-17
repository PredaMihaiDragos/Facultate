#pragma once

#include "Question.h"

class Number : public Question
{
private:
	int correct;
public:
	double GetScore();
};

