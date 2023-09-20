//
// Created by Tymoteusz Pilarz on 20/09/2023.
//

#include "Application.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(Application);

bool Application::OnInit()
{
    auto mainFrame = new MainFrame("Optical Distortion Correction");
    mainFrame->Show(true);
    return true;
}