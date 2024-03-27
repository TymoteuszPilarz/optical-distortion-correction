//
// Created by Tymoteusz Pilarz on 20/09/2023.
//

#ifndef OPTICAL_DISTORTION_CORRECTION_MENUBAR_H
#define OPTICAL_DISTORTION_CORRECTION_MENUBAR_H

#include <wx/menu.h>
#include <wx/event.h>
#include <wx/filename.h>

#include "DistortionEngine.h"

class MainFrame;

class MenuBar : public wxMenuBar
{
private:
    wxFileName imageFileName;
    wxFileName savedImageFileName;

    wxMenu* fileMenu;
    wxMenu* helpMenu;

    void FileMenuSetup();
    void HelpMenuSetup();

    void Open(wxCommandEvent& event);
    void Save(wxCommandEvent& event);
    void SaveAs(wxCommandEvent& event);
    void About(wxCommandEvent& event);

public:
    MenuBar();
};

#endif //OPTICAL_DISTORTION_CORRECTION_MENUBAR_H
