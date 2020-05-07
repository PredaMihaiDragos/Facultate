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

int Word::GetScore(const std::string& answer) const
{
	int dist = GetEditDistance(answer, correct);
	if (dist >= correct.size())
		return 0;
	double letterValue = 100.0 / static_cast<double>(correct.size());
	return round((correct.size() - dist) * letterValue);
}

int Word::GetEditDistance(const std::string& first, const std::string& second)
{
	int n = first.size(), m = second.size();
	std::vector<int> dp[2];
	dp[0].resize(m+1), dp[1].resize(m+1);

	for (int i = 0; i <= m; i++)
		dp[0][i] = i;

	for (int i = 1; i <= n; i++) 
	{
		dp[1][0] = i;
		for (int j = 1; j <= m; j++)
		{
			if (first[i-1] == second[j-1])
				dp[1][j] = dp[0][j - 1];
			else
				dp[1][j] = std::min(dp[0][j-1], std::min(dp[0][j], dp[1][j-1])) + 1;
		}
		dp[0] = dp[1];
	}
	return dp[0][m];
}

void Word::Show(wxFrame* container, std::function<void(int, std::string message)> submitCallback)
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