//
// Created by Tymoteusz Pilarz on 20/09/2023.
//

#include <wx/sizer.h>
#include <wx/dcclient.h>
#include <wx/bitmap.h>

#include "ImagePanel.h"
#include "DistortionEngine.h"

ImagePanel::ImagePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxFULL_REPAINT_ON_RESIZE)
{
    Bind(wxEVT_PAINT, &ImagePanel::Repaint, this);
}

void ImagePanel::Repaint(wxPaintEvent& event)
{
    auto image = DistortionEngine::GetInstance().GetResult();
    if (image == nullptr)
    {
        return;
    }

    wxPaintDC dc(this);

    int width, height;
    dc.GetSize(&width, &height);

    wxBitmap bitmap(image->Scale(width, height, wxIMAGE_QUALITY_BILINEAR));
    dc.DrawBitmap(bitmap, 0, 0);
}