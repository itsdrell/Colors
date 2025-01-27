#pragma once
#include "Widget.h"

///------------------------------------------------------------------
struct Camera2D;
class ColorSelectorButton;

///------------------------------------------------------------------
class ColorPickerWidget : public Widget
{

public:
    ColorPickerWidget(Camera2D* uiCamera, AABB2& bounds);

public:
    virtual void Update(float ds) override;
    virtual void Render() const override;

private:
    Camera2D* m_camera = nullptr;
    ColorSelectorButton* m_ColorSelectToggleButton = nullptr;

    bool m_isOpen = false;
};