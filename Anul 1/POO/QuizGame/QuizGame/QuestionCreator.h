#pragma once
#include "questions.h"

#include "dbModelCreator.h"
#include "QuestionCreationDialog.h"

class QuestionCreator : 
	public dbModelCreator
{
public:
	virtual ~QuestionCreator() {};
	virtual std::unique_ptr<Question> Create(const std::string& text) const = 0;
	virtual std::vector<std::unique_ptr<Question> > LoadAll() const = 0;
	virtual void ShowCreationDialog(wxWindow* parent, std::function<void(std::shared_ptr<Question>)> createdCallback) const = 0;
};