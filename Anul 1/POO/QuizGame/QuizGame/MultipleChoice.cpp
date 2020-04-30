#include "MultipleChoice.h"

double MultipleChoice::GetScore() const
{
	return 100.0;
}

void MultipleChoice::SetChoice(int index, const std::string &str)
{
	choice[index] = str;
}

MultipleChoice::MultipleChoice(const std::string& _text) : 
	Question(_text, "MultipleChoice")
{
	choice.resize(choices);
}

std::unordered_map<std::string, fieldType> MultipleChoice::toMap()
{
	std::unordered_map<std::string, fieldType> ret;
	ret["TEXT"] = &text;
	for (int i = 0; i < choice.size(); ++i)
		ret["CHOICE" + std::to_string(i)] = &choice[i];
	ret["CORRECT"] = &correct;
	return ret;
}