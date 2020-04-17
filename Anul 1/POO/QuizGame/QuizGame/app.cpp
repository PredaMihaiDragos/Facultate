#include "app.h"

wxIMPLEMENT_APP(app);

bool app::OnInit()
{
    frame = new GameFrame(GameFrameStyle::Window::title);
    frame->Show(true);
    return true;
}

int app::OnExit()
{
    return 1;
}