#include "MultipleChoice.h"

MultipleChoice::MultipleChoice() :
	Question(tableName)
{
	choice.resize(choices);
}

MultipleChoice::MultipleChoice(const std::string& _text) : 
	Question(_text, tableName)
{
	choice.resize(choices);
}

std::unordered_map<std::string, fieldType> MultipleChoice::toMap() const
{
	std::unordered_map<std::string, fieldType> ret;
	ret["TEXT"] = &text;
	for (int i = 0; i < choice.size(); ++i)
		ret["CHOICE" + std::to_string(i)] = &choice[i];
	ret["CORRECT"] = &correct;
	return ret;
}

double MultipleChoice::GetScore() const
{
	return 100.0;
}

void MultipleChoice::SetChoice(int index, const std::string& str)
{
	if (index > choices)
		throw std::out_of_range("Index " + std::to_string(index) + " is out of range!");
	choice[index] = str;
}

std::string MultipleChoice::GetChoice(int index) const
{
	if (index > choices)
		throw std::out_of_range("Index " + std::to_string(index) + " is out of range!");
	return choice[index];
}

void MultipleChoice::Show(wxFrame* container) const
{

}
