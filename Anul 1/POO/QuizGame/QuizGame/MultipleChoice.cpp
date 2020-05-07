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

int MultipleChoice::GetScore(const std::string& answer) const
{
	if(answer == correct)
		return 100.0;
	return 0.0;
}

void MultipleChoice::SetChoice(int index, const std::string& str)
{
	if (index > choices)
		throw Exception("Index " + std::to_string(index) + " is out of range!", "MultipleChoice.cpp");
	choice[index] = str;
}

std::string MultipleChoice::GetChoice(int index) const
{
	if (index > choices)
		throw Exception("Index " + std::to_string(index) + " is out of range!", "MultipleChoice.cpp");
	return choice[index];
}

void MultipleChoice::Show(wxFrame* container, std::function<void(int, std::string message)> submitCallback)
{
	using namespace GameFrameStyle::Question;
	auto *questionText = new wxStaticText(container, -1, GetText(), Text::pos, Text::size, Text::style);
	questionText->SetFont(Text::font);
	std::vector<wxStaticText*> inputChoice;
	std::vector<wxRadioButton*> inputRadio;

	for (int i = 0; i < choices; ++i)
	{
		wxPoint pos = Choice::pos + wxPoint(0, Choice::spaceY * i + Choice::paddingTop);
		wxStaticText* choice = new wxStaticText(container, wxID_ANY, GetChoice(i), pos, Choice::size, Choice::style);

		long style = Radio::style;
		if (i == 0)
			style |= wxRB_GROUP;
		pos += wxPoint(Choice::size.x + Radio::paddingLeft, Radio::paddingTop);
		wxRadioButton* radio = new wxRadioButton(container, wxID_ANY, wxEmptyString, pos, wxDefaultSize, style);

		inputChoice.push_back(choice);
		inputRadio.push_back(radio);
	}
	wxPoint submitPos = Submit::pos + wxPoint(0, Choice::pos.y + Choice::spaceY * choices);
	auto submitButton = new wxButton(container, wxID_ANY, Submit::label, submitPos, Submit::size);

	submitButton->Bind(wxEVT_BUTTON, [this, questionText, inputChoice, inputRadio, submitButton, submitCallback](wxCommandEvent& event) {
			int score = 0;
			for (int i = 0; i < choices; ++i)
			{
				if (inputRadio[i]->GetValue())
				{
					std::string inputValue = inputChoice[i]->GetLabel().ToStdString();
					score += GetScore(inputValue);
					break;
				}
			}
			std::string message;
			if (score < 100.0)
				message = "Wrong answer! Correct answer was: <" + this->correct + ">";
			else
				message = "Correct answer! Congratulations!";
			submitCallback(score, message);
			
			questionText->Destroy();
			for (int i = 0; i < choices; ++i)
			{
				inputChoice[i]->Destroy();
				inputRadio[i]->Destroy();
			}
			
			submitButton->Destroy();
		});
}
