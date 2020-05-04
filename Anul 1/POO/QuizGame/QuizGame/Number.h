#pragma once

#include "Question.h"

class Number : 
	public Question
{
private:
public:
	static constexpr const char tableName[] = "Number";
	Number();
	Number(const std::string& _text);
	double GetScore() const override;
	std::unordered_map<std::string, fieldType> toMap() const override;
	void Show(wxFrame* container) const override;
};

