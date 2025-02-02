#pragma once
#include "Widget.h"
#include <vector>

///------------------------------------------------------------------
struct Camera2D;
class ColorSelectorButton;
class Playing;
class GridColorButton;
class ColorSelectorNextPageButton;

///------------------------------------------------------------------
class ColorPickerWidget : public Widget
{

public:
    ColorPickerWidget(Camera2D* uiCamera, AABB2& bounds, Playing* playing);

public:
    virtual void Update(float ds) override;
    virtual void Render() const override;

    void UpdateButtonValues();

public:
    bool m_isOpen = false;

private:
    Camera2D* m_camera = nullptr;
    Playing* m_playing = nullptr;

    std::vector<GridColorButton*> m_gridColors;

private:
    AABB2 m_headerBounds;
    AABB2 m_closeBounds;

    AABB2 m_colorsBounds;

private:
    ColorSelectorButton* m_ColorSelectToggleButton = nullptr;

    bool m_showPageButtons = false;
    int m_currentPage = 0;
    int m_lastPage = 1;
    ColorSelectorNextPageButton* m_previousButton = nullptr;
    ColorSelectorNextPageButton* m_nextButton = nullptr;
};