#pragma once
#include "Widget.h"
#include <vector>

///------------------------------------------------------------------
struct Camera2D;
class ColorSelectorButton;
class Playing;
class GridColorButton;

///------------------------------------------------------------------
class ColorPickerWidget : public Widget
{

public:
    ColorPickerWidget(Camera2D* uiCamera, AABB2& bounds, Playing* playing);

public:
    virtual void Update(float ds) override;
    virtual void Render() const override;

public:
    bool m_isOpen = false;

private:
    Camera2D* m_camera = nullptr;
    Playing* m_playing = nullptr;

    ColorSelectorButton* m_ColorSelectToggleButton = nullptr;

    std::vector<GridColorButton*> m_gridColors;

private:
    AABB2 m_headerBounds;
    AABB2 m_closeBounds;

    AABB2 m_colorsBounds;
};