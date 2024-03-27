//
// Created by Tymoteusz Pilarz on 13/10/2023.
//

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/string.h>

#include "Element.h"
#include "MainFrame.h"

void Element::Scrolling(wxCommandEvent& event)
{
    auto value = static_cast<float>(slider->GetValue()) * precision;
    spinner->SetValue(value);

    auto& distortionCorrection = DistortionEngine::GetInstance();

    if (distortionType == DistortionType::radial)
    {
        distortionCorrection.SetRadDistCoeff(index, value * distortionCoeffScaler);
    }
    else if (distortionType == DistortionType::tangential)
    {
        distortionCorrection.SetTanDistCoeff(index, value * distortionCoeffScaler);
    }
}

void Element::StoppedScrolling(wxCommandEvent& event)
{
    DistortionEngine::GetInstance().Apply();
    static_cast<MainFrame*>(GetGrandParent()->GetGrandParent()->GetParent())->imagePanel->Refresh();
}

void Element::Spinning(wxSpinDoubleEvent& event)
{
    auto value = static_cast<float>(spinner->GetValue());
    slider->SetValue(static_cast<int>(value / precision));

    auto& distortionCorrection = DistortionEngine::GetInstance();

    if (distortionType == DistortionType::radial)
    {
        distortionCorrection.SetRadDistCoeff(index, value * distortionCoeffScaler);
    }
    else if (distortionType == DistortionType::tangential)
    {
        distortionCorrection.SetTanDistCoeff(index, value * distortionCoeffScaler);
    }
    distortionCorrection.Apply();
    static_cast<MainFrame*>(GetGrandParent()->GetGrandParent()->GetParent())->imagePanel->Refresh();
}

Element::Element(wxWindow* parent, int index, DistortionType distortionType) : wxPanel(parent), distortionType(distortionType), index(index)
{
    assert(index >= 0);

    SetMinSize(wxSize(wxDefaultSize.GetWidth(), 40));

    auto mainSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->AddSpacer(10);

    wxString elementName;
    if (distortionType == DistortionType::radial)
    {
        distortionCoeffScaler = pow(10.f, static_cast<float>(-(10 + 4 * (index))));
        elementName = "K";
    }
    else if (distortionType == DistortionType::tangential)
    {
        if (index < 2)
            distortionCoeffScaler = 0.000001f;
        else
        {
            distortionCoeffScaler = pow(10.f, static_cast<float>(-(7 + 3 * (index))));
        }
        elementName = "P";
    }
    auto text = new wxStaticText(this, wxID_ANY, elementName + wxString::Format("%d", index + 1), wxDefaultPosition, wxSize(33, wxDefaultSize.GetHeight()));
    mainSizer->Add(text, 0);

    slider->Bind(wxEVT_SCROLL_THUMBTRACK, &Element::Scrolling, this);
    slider->Bind(wxEVT_SCROLL_THUMBRELEASE, &Element::StoppedScrolling, this);
    mainSizer->Add(slider, 1);

    mainSizer->AddSpacer(10);

    spinner->Bind(wxEVT_SPINCTRLDOUBLE, &Element::Spinning, this);
    mainSizer->Add(spinner, 0);

    mainSizer->AddSpacer(10);

    SetSizer(mainSizer);

    if (distortionType == DistortionType::radial)
    {
        DistortionEngine::GetInstance().PushRadDistCoeff(0.f);
    }
    else if (distortionType == DistortionType::tangential)
    {
        DistortionEngine::GetInstance().PushTanDistCoeff(0.f);
    }
}
