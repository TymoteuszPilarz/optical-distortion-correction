//
// Created by Tymoteusz Pilarz on 13/10/2023.
//

#ifndef OPTICAL_DISTORTION_CORRECTION_PAGE_H
#define OPTICAL_DISTORTION_CORRECTION_PAGE_H

#include <wx/scrolwin.h>
#include <wx/sizer.h>

#include "DistortionEngine.h"

class Page : public wxScrolledWindow
{
private:
    const int initialElementCount = 2;

    const DistortionType distortionType;

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

public:
    Page(wxWindow* parent, DistortionType distortionType);

    void AddElement();
    void DeleteElement();

    [[nodiscard]] bool IsEmpty() const;
    [[nodiscard]] bool IsFull() const;

    void Reset();
};

#endif //OPTICAL_DISTORTION_CORRECTION_PAGE_H
