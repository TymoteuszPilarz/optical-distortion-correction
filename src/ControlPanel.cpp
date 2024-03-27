//
// Created by Tymoteusz Pilarz on 27/09/2023.
//

#include <wx/sizer.h>
#include <wx/button.h>

#include "ControlPanel.h"
#include "Page.h"
#include "DistortionEngine.h"

void ControlPanel::PageChanged(wxNotebookEvent& event)
{
    auto currentPage = static_cast<Page*>(notebook->GetCurrentPage());

    if (currentPage->IsEmpty())
    {
        deleteButton->Disable();
    }
    else
    {
        deleteButton->Enable();
    }

    if (currentPage->IsFull())
    {
        addButton->Disable();
    }
    else
    {
        addButton->Enable();
    }

    currentPage->SetFocusIgnoringChildren(); // Prevent wxSpinCtrl elements from gaining unwanted focus while changing pages
}

void ControlPanel::AddElement(wxCommandEvent& event)
{
    auto currentPage = static_cast<Page*>(notebook->GetCurrentPage());

    currentPage->AddElement();

    if (currentPage->IsFull())
    {
        addButton->Disable();
    }

    deleteButton->Enable();
}

void ControlPanel::DeleteElement(wxCommandEvent& event)
{
    auto currentPage = static_cast<Page*>(notebook->GetCurrentPage());

    currentPage->DeleteElement();

    if (currentPage->IsEmpty())
    {
        deleteButton->Disable();
    }

    addButton->Enable();
}

ControlPanel::ControlPanel(wxWindow* parent) : wxPanel(parent)
{
    auto mainSizer = new wxBoxSizer(wxVERTICAL);

    notebook->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &ControlPanel::PageChanged, this);

    auto firstPage = new Page(notebook, DistortionType::radial);
    notebook->AddPage(firstPage, "radial");

    auto secondPage = new Page(notebook, DistortionType::tangential);
    notebook->AddPage(secondPage, "tangential");

    mainSizer->Add(notebook, 1, wxEXPAND);

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->SetMinSize(wxButton::GetDefaultSize().GetWidth() * 2 + 15, wxButton::GetDefaultSize().GetHeight() + 8);
    buttonSizer->AddStretchSpacer(1);

    addButton->Bind(wxEVT_BUTTON, &ControlPanel::AddElement, this);
    buttonSizer->Add(addButton, 0, wxALIGN_CENTER);

    buttonSizer->AddSpacer(4);

    deleteButton->Bind(wxEVT_BUTTON, &ControlPanel::DeleteElement, this);
    buttonSizer->Add(deleteButton, 0, wxALIGN_CENTER);

    buttonSizer->AddStretchSpacer(1);

    mainSizer->Add(buttonSizer, 0, wxEXPAND);

    SetSizer(mainSizer);
}

void ControlPanel::Reset()
{
    static_cast<Page*>(notebook->GetPage(0))->Reset();
    static_cast<Page*>(notebook->GetPage(1))->Reset();
}