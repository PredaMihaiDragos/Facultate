#include "Number.h"

Number::Number() :
	Question(tableName)
{}

Number::Number(const std::string& _text) :
	Question(_text, tableName)
{}


int Number::GetScore(const std::string& answer) const
{
	if (answer == correct)
		return 100.0;
	return 0.0;
}

std::unordered_map<std::string, fieldType> Number::toMap() const
{
	std::unordered_map<std::string, fieldType> ret;
	ret["TEXT"] = &text;
	ret["CORRECT"] = &correct;
	return ret;
}

void Number::Show(wxFrame* container, std::function<void(int, std::string message)> submitCallback)
{
	using namespace GameFrameStyle::Question;
	auto questionText = new wxStaticText(container, -1, GetText(), Text::pos, Text::size, Text::style);
	questionText->SetFont(Text::font);

	auto inputAnswer = new wxTextCtrl(container, wxID_ANY, wxEmptyString, Answer::pos, Answer::size, Answer::style);
	inputAnswer->SetHint(Answer::hint);
	wxPoint submitPos = Submit::pos + wxPoint(0, Answer::pos.y + Answer::size.y);

	auto submitButton = new wxButton(container, wxID_ANY, Submit::label, submitPos, Submit::size);
	submitButton->Bind(wxEVT_BUTTON, [this, questionText, inputAnswer, submitButton, submitCallback](wxCommandEvent& event) {
		int score = GetScore(inputAnswer->GetValue().ToStdString());
		std::string message;
		if (score < 100.0)
			message = "Wrong answer! Correct answer was: <" + this->correct + ">. You got " + std::to_string(score) + " points.";
		else
			message = "Correct answer! Congratulations!";
		submitCallback(score, message);

		questionText->Destroy();
		inputAnswer->Destroy();
		submitButton->Destroy();
	});
}
