//
// Created by Tymoteusz Pilarz on 20/09/2023.
//

#include <memory>

#include <wx/menuitem.h>
#include <wx/filedlg.h>
#include <wx/utils.h>

#include "MenuBar.h"
#include "MainFrame.h"

void MenuBar::FileMenuSetup()
{
    fileMenu = new wxMenu;
    Append(fileMenu, "File");

    auto openMenuItem = new wxMenuItem(fileMenu, wxID_OPEN);
    auto saveMenuItem = new wxMenuItem(fileMenu, wxID_SAVE);
    auto saveAsMenuItem = new wxMenuItem(fileMenu, wxID_SAVEAS);
    auto exitMenuItem = new wxMenuItem(fileMenu, wxID_EXIT);

    fileMenu->Append(openMenuItem);
    fileMenu->Append(saveMenuItem);
    fileMenu->Append(saveAsMenuItem);
    fileMenu->Append(wxID_SEPARATOR);
    fileMenu->Append(wxID_SEPARATOR);
    fileMenu->Append(exitMenuItem);

    fileMenu->Enable(saveMenuItem->GetId(), false);
    fileMenu->Enable(saveAsMenuItem->GetId(), false);

    fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, &MenuBar::Open, this, openMenuItem->GetId());
    fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, &MenuBar::Save, this, saveMenuItem->GetId());
    fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, &MenuBar::SaveAs, this, saveAsMenuItem->GetId());
}

void MenuBar::HelpMenuSetup()
{
    helpMenu = new wxMenu;
    Append(helpMenu, "&Help");

    auto aboutMenuItem = new wxMenuItem(helpMenu, wxID_ABOUT);

    helpMenu->Append(aboutMenuItem);

    helpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, &MenuBar::About, this, aboutMenuItem->GetId());
}

void MenuBar::Open(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, "Choose image to open", "", "", "Image files (*.bmp, *.jpg, *.jpeg, *.png)|*.bmp;*.jpg;*.jpeg;*.png;" , wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() != wxID_CANCEL)
    {
        fileMenu->Enable(wxID_SAVE, true);
        fileMenu->Enable(wxID_SAVEAS, true);

        imageFileName = openFileDialog.GetPath();
        savedImageFileName.Clear();

        auto image = std::make_unique<wxImage>();
        image->LoadFile(openFileDialog.GetPath());

        DistortionEngine::GetInstance().SetImage(std::move(image));

        auto mainFrame = static_cast<MainFrame*>(GetFrame());
        mainFrame->RecalcImageSize();
        mainFrame->controlPanel->Reset();
    }
}

void MenuBar::Save(wxCommandEvent& event)
{
    auto image = DistortionEngine::GetInstance().GetResult();
    assert(image != nullptr);

    if (savedImageFileName == "")
    {
        SaveAs(event);
    }
    else
    {
        image->SaveFile(savedImageFileName.GetFullPath());
    }
}

void MenuBar::SaveAs(wxCommandEvent& event)
{
    auto image = DistortionEngine::GetInstance().GetResult();
    assert(image != nullptr);

    wxFileDialog saveFileDialog(this, "Choose where to save the image", imageFileName.GetPath(), imageFileName.GetName() + "_out." + imageFileName.GetExt(), wxString("Image file (*.") + imageFileName.GetExt() + ")|*." + imageFileName.GetExt(), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() != wxID_CANCEL)
    {
        image->SaveFile(saveFileDialog.GetPath());
        savedImageFileName = saveFileDialog.GetPath();
    }
}

void MenuBar::About(wxCommandEvent& event)
{
    wxLaunchDefaultBrowser("https://github.com/TymoteuszPilarz/optical-distortion-correction");
}

MenuBar::MenuBar()
{
    FileMenuSetup();
    HelpMenuSetup();
}