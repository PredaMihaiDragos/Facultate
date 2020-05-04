#include "Word.h"

Word::Word() :
	Question("Word")
{}

Word::Word(const std::string& _text) :
	Question(_text, tableName)
{}

std::unordered_map<std::string, fieldType> Word::toMap() const
{
	std::unordered_map<std::string, fieldType> ret;
	ret["TEXT"] = &text;
	ret["CORRECT"] = &correct;
	return ret;
}

void Word::Show(wxFrame* container) const
{
}

double Word::GetScore() const
{
	return 90.0;
}