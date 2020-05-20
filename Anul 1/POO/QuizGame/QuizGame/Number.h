#pragma once

#include "Question.h"
#include "style.h"

class Number : 
	public Question
{
public:
	static constexpr const char tableName[] = "Number";
	Number();
	virtual ~Number() {};
	Number(const std::string& _text);
	int GetScore(const std::string& answer) const override;
	std::unordered_map<std::string, fieldType> toMap() const override;
	void Show(wxFrame* container, std::function<void(int, std::string message)> submitCallback) override;
};

