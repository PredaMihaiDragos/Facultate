#include "app.h"

wxIMPLEMENT_APP(app);

bool app::OnInit()
{
    frame = new GameFrame("QuizGame by Mihai Preda");
    frame->Show(true);
    return true;
}

int app::OnExit()
{
    return 0;
}