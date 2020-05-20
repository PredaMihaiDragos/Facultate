#pragma once

#include "Question.h"
#include "style.h"

class Word : public Question
{
public:
	static constexpr const char tableName[] = "Word";
	Word();
	virtual ~Word() {};
	Word(const std::string& _text);
	int GetScore(const std::string& answer) const override;
	static int GetEditDistance(const std::string& first, const std::string& second);
	std::unordered_map<std::string, fieldType> toMap() const override;
	void Show(wxFrame* container, std::function<void(int, std::string message)> submitCallback) override;
};
