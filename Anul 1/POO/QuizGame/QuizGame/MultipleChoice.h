#pragma once

#include "Question.h"
#include "style.h"

class MultipleChoice : 
	public Question
{

public:
	static const int choices = 4;
	static constexpr const char tableName[] = "MultipleChoice";
	MultipleChoice();
	MultipleChoice(const std::string &_text);
	double GetScore(const std::string& answer) const override;
	std::unordered_map<std::string, fieldType> toMap() const override;
	void SetChoice(int index, const std::string& str);
	std::string GetChoice(int index) const;
	void Show(wxFrame* container, std::function<void(double)> submitCallback) override;

private:
	std::vector<std::string> choice;
};
