#pragma once

namespace QuestionDialogStyle
{
	namespace Window
	{
		const wxString title = "Add question";
		const wxPoint pos = wxDefaultPosition;
		const wxSize size = wxSize(400, 600);
	}

	namespace QuestionType
	{
		namespace MultipleChoice
		{
			const wxString title = "Multiple Choice";
			const wxPoint pos = wxPoint(10, 10);
		}
		namespace Word
		{
			const wxString title = "Word";
			const wxPoint pos = wxPoint(120, 10);
		}
		namespace Number
		{
			const wxString title = "Number";
			const wxPoint pos = wxPoint(200, 10);
		}
	}

	namespace Create
	{
		namespace Question
		{
			const wxPoint pos = wxPoint(10, 10);
			const wxSize size = wxSize(300, 40);
			const wxString hint = "Question";
			const long style = wxTE_MULTILINE;
			const int spaceY = pos.y;
		}
		namespace Choice
		{
			using namespace QuestionDialogStyle::Create;
			const wxPoint pos = wxPoint(10, 10 + Question::size.y);
			const wxSize size = wxSize(200, 40);
			const wxString hint = "Input choice";
			const int paddingTop = 10;
			const long style = 0L;
			const int spaceY = size.y + paddingTop;
		}
		namespace Radio
		{
			const long style = 0L;
			const int paddingLeft = 10;
			const int paddingTop = 12;
		}
		namespace Answer
		{
			using namespace QuestionDialogStyle::Create;
			const wxPoint pos = wxPoint(10, 20 + Question::pos.y + Question::size.y);
			const wxSize size = wxSize(200, 40);
			const wxString hint = "Answer";
			const long style = 0L;
			const int spaceY = pos.y;
		}
		namespace Submit
		{
			const wxString label = "Submit";
			const wxPoint pos = wxPoint(100, 15);
			const wxSize size = wxSize(200, 40);
		}
	}
}