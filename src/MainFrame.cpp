//
// Created by Tymoteusz Pilarz on 20/09/2023.
//

#include <wx/sizer.h>

#include "MainFrame.h"
#include "DistortionEngine.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
    MainFrame::SetMenuBar(static_cast<wxMenuBar*>(menuBar));

    auto mainSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->SetMinSize(700, 400);

    auto mainSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE | wxSP_3DSASH);
    mainSplitter->SetSashGravity(0.25);

    mainSplitter->SetMinimumPaneSize(20);
    mainSizer->Add(mainSplitter, 1 , wxEXPAND);

    auto imagePanelHolder = new wxPanel(mainSplitter);
    imagePanelHolder->SetSizer(imagePanelSizer);
    imagePanel = new ImagePanel(imagePanelHolder);

    controlPanel = new ControlPanel(mainSplitter);

    mainSplitter->SplitVertically(controlPanel, imagePanelHolder, 125);

    SetSizerAndFit(mainSizer);
}

void MainFrame::RecalcImageSize()
{
    auto image = DistortionEngine::GetInstance().GetResult();
    assert(image != nullptr);

    imagePanelSizer->Detach(imagePanel);

    imagePanel->SetSize(image->GetWidth(), image->GetHeight());
    imagePanel->Refresh();

    imagePanelSizer->Add(imagePanel, 1, wxSHAPED | wxALIGN_CENTER);
    imagePanelSizer->Layout();
}
