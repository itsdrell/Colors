#pragma once
#include "Button.h"

class GridColorButton : public Button
{
public:
    GridColorButton(AABB2& bounds)
        : Button(bounds) {};

public:
    void Init(Color& color, int index, int* amountLeft, bool isSelected)
    {
        m_color = color;
        m_index = index;
        m_amountLeftPointer = amountLeft;
        m_isSelectedColor = isSelected;
    }

public:
    virtual void Render() const override;

public:
    Color   m_color = PINK;
    int     m_index = -1;

    int*    m_amountLeftPointer = nullptr;

    bool    m_isSelectedColor = false;
};