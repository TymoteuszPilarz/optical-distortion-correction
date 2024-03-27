//
// Created by Tymoteusz Pilarz on 20/09/2023.
//

#ifndef OPTICAL_DISTORTION_CORRECTION_MAINFRAME_H
#define OPTICAL_DISTORTION_CORRECTION_MAINFRAME_H

#include <memory>

#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/splitter.h>
#include <wx/image.h>
#include <wx/string.h>

#include "MenuBar.h"
#include "ControlPanel.h"
#include "ImagePanel.h"

class MainFrame: public wxFrame
{
    friend class MenuBar;
    friend class Page;
    friend class Element;

private:
    MenuBar* menuBar = new MenuBar();

    wxBoxSizer* imagePanelSizer = new wxBoxSizer(wxHORIZONTAL);

    ControlPanel* controlPanel;
    ImagePanel* imagePanel;

public:
    explicit MainFrame(const wxString& title);

    void RecalcImageSize();
};

#endif //OPTICAL_DISTORTION_CORRECTION_MAINFRAME_H
