#pragma once
#include "Widget.h"

class Button : public Widget
{
public:
    Button(AABB2& bounds)
        : Widget(bounds) {};

public:
    virtual bool OnClicked() { return false; };
};