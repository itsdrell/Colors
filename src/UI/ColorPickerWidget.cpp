#include "ColorPickerWidget.h"
#include "ColorSelectorButton.h"
#include "raylib.h"
#include "GameUtils.h"
#include "Playing.h"
#include "GridColorButton.h"

///------------------------------------------------------------------
ColorPickerWidget::ColorPickerWidget(Camera2D* uiCamera, AABB2& bounds, Playing* playing)
    : Widget(bounds)
{
    m_camera = uiCamera;
    m_playing = playing;

    AABB2 buttonBounds = GetAABB2FromAABB2({.85, .85}, {.95, .9}, m_bounds);
    m_ColorSelectToggleButton = new ColorSelectorButton(buttonBounds);

    m_headerBounds = GetAABB2FromAABB2({ 0.f, 0.f }, { 1.f, .1f }, m_bounds);
    m_closeBounds = GetAABB2FromAABB2({ 0.9f, 0.1f }, { .98f, .6f }, m_headerBounds);

    m_colorsBounds = GetAABB2FromAABB2({.15, .15}, {.85, .9}, m_bounds);

    int amountOfColors = (playing->m_colors.size() < 18) ? playing->m_colors.size() - 1 : 18;

    float colorButtonWidth = .2;
    float colorButtonHeight = .15;

    float minY = .025;
    float minX = .1;
    for(int height = 0; height < 5; height++)
    {
        for(int width = 0; width < 3; width++)
        {
            AABB2 bounds = GetAABB2FromAABB2({ minX, minY }, { minX + colorButtonWidth, minY + colorButtonHeight }, m_colorsBounds);
            GridColorButton* newColor = new GridColorButton(bounds);

            int index = height * 3 + width;
            if (index > amountOfColors)
                break;

            // live updates
            ColorLookup color = ColorToInt(m_playing->m_colors[index]);
            int* intPoint = &playing->m_ColorProgress[color];

            //newColor->Init(m_playing->m_colors[index], index, 69);
            newColor->Init(m_playing->m_colors[index], index, intPoint);
            m_gridColors.push_back(newColor);

            minX += .3;
        }

        minX = .1;
        minY += .2;
    }
}

///------------------------------------------------------------------
void ColorPickerWidget::Update(float ds)
{
    Vector2 mousePos = GetMousePosition();
    
    // Input
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        if (m_isOpen == false)
        {
            if (m_ColorSelectToggleButton->IsSelected(mousePos))
            {
                m_isOpen = true;
                return;
            }
        }
        else
        {
            if (m_closeBounds.IsPointInBox(mousePos))
            {
                m_isOpen = false;
                return;
            }

            for (const GridColorButton* currentColor : m_gridColors)
            {
                if (currentColor->IsSelected(mousePos))
                {
                    m_playing->m_selected_color = currentColor->m_index;
                }
            }
        }

        if (m_isOpen == false)
        {

        }
        else
        {

        }

    }
}

///------------------------------------------------------------------
void ColorPickerWidget::Render() const
{
    if (m_isOpen == false)
    {
        m_ColorSelectToggleButton->Render();
        return;
    }

    DrawAABB2(m_bounds, WHITE);
    
    
    DrawAABB2(m_headerBounds, WHITE);
    DrawAABB2(m_closeBounds, RED);
    DrawAABB2(m_colorsBounds, WHITE);

    for(GridColorButton* color : m_gridColors)
    {
        color->Render();
    }
}