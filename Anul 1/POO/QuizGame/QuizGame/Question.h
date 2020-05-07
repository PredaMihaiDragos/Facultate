#pragma once

#include <vector>
#include <string>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/display.h>
#include <wx/dialog.h>

#include "dbModel.h"

class Question: 
	public dbModel
{
protected:
	std::string text;
	std::string correct;
public:
	virtual ~Question() {};
	Question(const std::string& tableName);
	Question(const std::string& _text, const std::string &tableName);
	virtual void Show(wxFrame * container, std::function<void(int, std::string message)> submitCallback) = 0;
	void SetText(const std::string &text) { this->text = text; }
	std::string GetText() const { return text;  }
	virtual int GetScore(const std::string &answer) const = 0;
	void operator()(wxFrame* container, std::function<void(int, std::string message)> submitCallback) { Show(container, submitCallback); };
	void SetCorrect(const std::string& correct) { this->correct = correct;  }
};

