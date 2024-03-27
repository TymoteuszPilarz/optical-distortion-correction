//
// Created by Tymoteusz Pilarz on 13/10/2023.
//

#ifndef OPTICAL_DISTORTION_CORRECTION_ELEMENT_H
#define OPTICAL_DISTORTION_CORRECTION_ELEMENT_H

#include <wx/panel.h>
#include <wx/string.h>
#include <wx/slider.h>
#include <wx/spinctrl.h>

#include "DistortionEngine.h"

class Element : public wxPanel
{
private:
    const int index;

    const DistortionType distortionType;
    float distortionCoeffScaler;

    const int minValue = -100;
    const int maxValue = 100;
    /// Precision can be only in the form of 10^(-n), where n is an integer value greater than or equal to 0
    const float precision = 0.1;

    const int ctrlMaxValue = static_cast<int>(static_cast<float>(0) + static_cast<float>(maxValue - minValue) / precision);

    wxSlider* slider = new wxSlider(this, wxID_ANY, 0, minValue * static_cast<int>(1 / precision), maxValue * static_cast<int>(1 / precision));
    wxSpinCtrlDouble* spinner = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, minValue, maxValue, 0.0, precision);

protected:
    void Scrolling(wxCommandEvent& event);
    void StoppedScrolling(wxCommandEvent& event);
    void Spinning(wxSpinDoubleEvent& event);

public:
    Element(wxWindow* parent, int index, DistortionType distortionType);
};

#endif //OPTICAL_DISTORTION_CORRECTION_ELEMENT_H
