//
// Created by Tymoteusz Pilarz on 27/09/2023.
//

#ifndef OPTICAL_DISTORTION_CORRECTION_CONTROLPANEL_H
#define OPTICAL_DISTORTION_CORRECTION_CONTROLPANEL_H

#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/button.h>

class ControlPanel : public wxPanel
{
private:
    wxNotebook* notebook = new wxNotebook(this, wxID_ANY);

    wxButton* addButton = new wxButton(this, wxID_ANY, "Add");
    wxButton* deleteButton = new wxButton(this, wxID_ANY, "Delete");

    void PageChanged(wxNotebookEvent& event);
    void AddElement(wxCommandEvent& event);
    void DeleteElement(wxCommandEvent& event);

public:
    explicit ControlPanel(wxWindow* parent);

    void Reset();
};

#endif //OPTICAL_DISTORTION_CORRECTION_CONTROLPANEL_H
