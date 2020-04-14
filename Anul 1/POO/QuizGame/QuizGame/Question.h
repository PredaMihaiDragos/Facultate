#pragma once

#include <vector>
#include <string>

class Question
{
protected:
	std::string text;
public:
	void SetText(std::string text) { this->text = text; }
	std::string GetText() { return text;  }

	virtual double GetScore() = 0;

};

