#pragma once

#include <vector>
#include <string>
#include "dbModel.h"

class Question: public dbModel
{
protected:
	std::string text;
	std::string correct;
public:
	virtual ~Question(){}
	Question(const std::string& _text, const std::string &tableName);
	void SetText(const std::string &text) { this->text = text; }
	std::string GetText() { return text;  }

	virtual double GetScore() const = 0;
	void SetCorrect(const std::string& correct) { this->correct = correct;  }
};

