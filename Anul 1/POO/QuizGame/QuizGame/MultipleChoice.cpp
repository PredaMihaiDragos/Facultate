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

double MultipleChoice::GetScore(const std::string& answer) const
{
	if(answer == correct)
		return 100.0;
	return 0.0;
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

void MultipleChoice::Show(wxFrame* container, std::function<void(double)> submitCallback)
{
	using namespace GameFrameStyle::Question;
	auto *questionText = new wxStaticText(container, -1, GetText(), Text::pos, Text::size, Text::style);
	questionText->SetFont(Text::font);
	std::vector<wxStaticText*> inputChoice;
	std::vector<wxRadioButton*> inputRadio;

	wxPoint submitPos = Submit::pos + wxPoint(0, Text::size.y);
	for (int i = 0; i < choices; ++i)
	{
		wxPoint pos = Choice::pos + wxPoint(0, Choice::spaceY * i + Choice::paddingTop);
		wxStaticText* choice = new wxStaticText(container, wxID_ANY, GetChoice(i), pos, Choice::size, Choice::style);

		long style = Radio::style;
		if (i == 0)
			style |= wxRB_GROUP;
		pos += wxPoint(Choice::size.x + Radio::paddingLeft, Radio::paddingTop);
		wxRadioButton* radio = new wxRadioButton(container, wxID_ANY, wxEmptyString, pos, Choice::size, style);

		inputChoice.push_back(choice);
		inputRadio.push_back(radio);
	}
	submitPos += wxPoint(0, Choice::spaceY * choices);
	auto submitButton = new wxButton(container, wxID_ANY, QuestionDialogStyle::Create::Submit::label, submitPos, QuestionDialogStyle::Create::Submit::size);
	submitButton->Bind(wxEVT_BUTTON, [this, questionText, inputChoice, inputRadio, submitButton, submitCallback](wxCommandEvent& event) {
			double score = 0;
			for (int i = 0; i < choices; ++i)
			{
				if (inputRadio[i]->GetValue())
				{
					std::string inputValue = inputChoice[i]->GetLabel().ToStdString();
					score += GetScore(inputValue);
					break;
				}
			}
			submitCallback(score);
			
			questionText->Destroy();
			for (int i = 0; i < choices; ++i)
			{
				inputChoice[i]->Destroy();
				inputRadio[i]->Destroy();
			}
			
			submitButton->Destroy();
		});
}
