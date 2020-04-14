#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


#include "GameFrame.h"

class app : public wxApp
{
private:
    GameFrame* frame;
public:
    bool OnInit();
    int OnExit();
};

