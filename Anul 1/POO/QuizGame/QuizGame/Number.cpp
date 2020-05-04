#include "Number.h"

Number::Number() :
	Question(tableName)
{}

Number::Number(const std::string& _text) :
	Question(_text, tableName)
{}


double Number::GetScore() const
{
	return 80.0;
}

std::unordered_map<std::string, fieldType> Number::toMap() const
{
	std::unordered_map<std::string, fieldType> ret;
	ret["TEXT"] = &text;
	ret["CORRECT"] = &correct;
	return ret;
}

void Number::Show(wxFrame* container) const
{
}
