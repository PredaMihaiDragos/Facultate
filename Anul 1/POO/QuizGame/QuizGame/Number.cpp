#include "Number.h"

double Number::GetScore() const
{
	return 80.0;
}

Number::Number(const std::string& _text) :
	Question(_text, "Number")
{}

std::unordered_map<std::string, fieldType> Number::toMap()
{
	std::unordered_map<std::string, fieldType> ret;
	ret["TEXT"] = &text;
	ret["CORRECT"] = &correct;
	return ret;
}