#pragma once
#include "Button.h"
#include <string>

///------------------------------------------------------------------
class ColorSelectorNextPageButton : public Button
{
public:
    ColorSelectorNextPageButton(AABB2& bounds, const std::string& textToDraw)
        : Button(bounds), m_displayText(textToDraw) {};

public:
    virtual void Render() const override;

private:
    std::string     m_displayText;
};

///------------------------------------------------------------------
