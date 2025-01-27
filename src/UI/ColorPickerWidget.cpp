#include "ColorPickerWidget.h"
#include "ColorSelectorButton.h"
#include "raylib.h"
#include "GameUtils.h"

///------------------------------------------------------------------
ColorPickerWidget::ColorPickerWidget(Camera2D* uiCamera, AABB2& bounds)
    : Widget(bounds)
{
    m_camera = uiCamera;

    AABB2 buttonBounds = GetAABB2FromAABB2({.85, .85}, {.95, .9}, m_bounds);
    m_ColorSelectToggleButton = new ColorSelectorButton(buttonBounds);
}

///------------------------------------------------------------------
void ColorPickerWidget::Update(float ds)
{
    Vector2 mousePos = GetMousePosition();
    
    if(m_isOpen == false)
    {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if(m_ColorSelectToggleButton->IsSelected(mousePos))
            {
                m_isOpen = true;
            }
        }
    }


}

///------------------------------------------------------------------
void ColorPickerWidget::Render() const
{
    if (m_isOpen == false)
    {
        m_ColorSelectToggleButton->Render();
    }

    DrawAABB2(m_bounds, WHITE);
}