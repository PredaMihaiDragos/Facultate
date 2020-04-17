#pragma once

namespace GameFrameStyle
{
	namespace Window
	{
		const wxString title = "QuizGame by Mihai Preda";
		const wxString status = "Welcome to QuizGame!";
		const wxPoint pos = wxPoint(480, 270);
		const wxSize size = wxSize(960, 540);
	}

	namespace Menu
	{
		namespace File
		{
			const wxString addQuestion = "&Add question\tCtrl-Q";
		}
		namespace Help
		{
			const wxString aboutMessage = "This is a QuizGame by Mihai Preda";
			const wxString aboutTitle = "About QuizGame";
		}
	}
}
