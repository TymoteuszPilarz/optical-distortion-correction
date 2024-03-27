//
// Created by Tymoteusz Pilarz on 20/09/2023.
//

#include <wx/image.h>
#include <wx/imagjpeg.h>
#include <wx/imagpng.h>

#include "Application.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(Application);

bool Application::OnInit()
{
    wxImage::AddHandler(new wxJPEGHandler);
    wxImage::AddHandler(new wxPNGHandler);

    auto mainFrame = new MainFrame("Optical Distortion Correction");
    mainFrame->Show(true);

    return true;
}