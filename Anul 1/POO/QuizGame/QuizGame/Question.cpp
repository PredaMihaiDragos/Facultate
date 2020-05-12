#include "Question.h"

Question::Question(const std::string& _text, const std::string & tableName) : 
	dbModel(tableName),
	text(_text)
{}

Question::Question(const std::string& tableName) :
	dbModel(tableName)
{}