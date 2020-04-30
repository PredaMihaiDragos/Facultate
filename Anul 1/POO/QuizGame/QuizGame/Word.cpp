#include "Word.h"

double Word::GetScore() const
{
	return 90.0;
}

Word::Word(const std::string& _text) :
	Question(_text, "Word")
{}

std::unordered_map<std::string, fieldType> Word::toMap()
{
	std::unordered_map<std::string, fieldType> ret;
	ret["TEXT"] = &text;
	ret["CORRECT"] = &correct;
	return ret;
}