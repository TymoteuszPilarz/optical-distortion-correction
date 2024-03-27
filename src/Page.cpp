//
// Created by Tymoteusz Pilarz on 13/10/2023.
//

#include "Page.h"
#include "Element.h"
#include "MainFrame.h"

Page::Page(wxWindow* parent, DistortionType distortionType) : wxScrolledWindow(parent), distortionType(distortionType)
{
    SetSizer(mainSizer);
    SetScrollRate(5, 5);

    for (int i = 0; i < initialElementCount; ++i)
    {
        AddElement();
    }
}

void Page::AddElement()
{
    assert(!IsFull());

    mainSizer->Add(new Element(this, static_cast<int>(mainSizer->GetItemCount()), distortionType), 0, wxEXPAND);
    mainSizer->Layout();

    FitInside();
}

void Page::DeleteElement()
{
    assert(!IsEmpty());

    auto index = static_cast<int>(mainSizer->GetItemCount()) - 1;
    auto item = mainSizer->GetItem(index)->GetWindow();
    mainSizer->Detach(index);
    item->Destroy();

    if (distortionType == DistortionType::radial)
    {
        DistortionEngine::GetInstance().PopRadDistCoeff();
    }
    else
    {
        DistortionEngine::GetInstance().PopTanDistCoeff();
    }

    DistortionEngine::GetInstance().Apply();
    static_cast<MainFrame*>(GetGrandParent()->GetGrandParent())->imagePanel->Refresh();

    FitInside();
}

bool Page::IsEmpty() const
{
    return mainSizer->IsEmpty();
}

bool Page::IsFull() const
{
    return mainSizer->GetItemCount() == 99;
}

void Page::Reset()
{
    while (!IsEmpty())
    {
        DeleteElement();
    }

    for (int i = 0; i < initialElementCount; ++i)
    {
        AddElement();
    }
}