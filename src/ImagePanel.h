//
// Created by Tymoteusz Pilarz on 20/09/2023.
//

#ifndef OPTICAL_DISTORTION_CORRECTION_IMAGEPANEL_H
#define OPTICAL_DISTORTION_CORRECTION_IMAGEPANEL_H

#include <wx/panel.h>

class MainFrame;

class ImagePanel : public wxPanel
{
public:
    explicit ImagePanel(wxWindow* parent);

    void Repaint(wxPaintEvent& event);
};

#endif //OPTICAL_DISTORTION_CORRECTION_IMAGEPANEL_H
