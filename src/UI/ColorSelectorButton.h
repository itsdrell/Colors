#pragma once
#include "Button.h"

class ColorSelectorButton : public Button
{
public:
    ColorSelectorButton(AABB2& bounds)
        : Button(bounds) {};

public:
    virtual void Render() const override;
    virtual bool OnClicked();
};
