#pragma once

namespace GameFrameStyle
{
	namespace Window
	{
		const wxString title = "QuizGame by Mihai Preda";
		const wxString scoreMessage = "Your score: ";
		const wxPoint pos = wxPoint(480, 270);
		const wxSize size = wxSize(960, 540);
		const wxColour colour = *wxWHITE;
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

	namespace Question
	{
		namespace Text
		{
			const wxPoint pos = wxDefaultPosition;
			const wxSize size = wxSize(950, 60);
			const long style = wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE;
			const wxFont font = wxFont(wxFontInfo(15).Bold());
		}
		namespace Choice
		{
			const wxPoint pos = wxPoint(280, 70);
			const wxSize size = wxSize(400, 60);
			const int paddingTop = 5;
			const long style = wxALIGN_CENTRE_HORIZONTAL;
			const int spaceY = size.y + paddingTop;
		}
		namespace Radio
		{
			const long style = 0L;
			const int paddingLeft = 10;
			const int paddingTop = 0;
		}
		namespace Answer
		{
			using namespace GameFrameStyle::Question;
			const wxPoint pos = wxPoint(380, Text::pos.y + Text::size.y + 20);
			const wxSize size = wxSize(200, 40);
			const wxString hint = "Answer";
			const long style = 0L;
			const int spaceY = pos.y;
		}
		namespace Submit
		{
			const wxString label = "Submit";
			const wxPoint pos = wxPoint(380, 30);
			const wxSize size = wxSize(200, 40);
		}
	}
}
