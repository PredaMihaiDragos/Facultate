#pragma once

#include "Question.h"

class MultipleChoice : 
	public Question
{

public:
	static const int choices = 4;
	static constexpr const char tableName[] = "MultipleChoice";
	MultipleChoice();
	MultipleChoice(const std::string &_text);
	double GetScore() const override;
	std::unordered_map<std::string, fieldType> toMap() const override;
	void SetChoice(int index, const std::string& str);
	std::string GetChoice(int index) const;
	void Show(wxFrame* container) const override;

private:
	std::vector<std::string> choice;
};
