#pragma once
#include "Question.h"

class Word : public Question
{
private:
public:
	static constexpr const char tableName[] = "Word";
	Word();
	Word(const std::string& _text);
	double GetScore() const override;
	std::unordered_map<std::string, fieldType> toMap() const override;
	void Show(wxFrame* container) const override;
};
