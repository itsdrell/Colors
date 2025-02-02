#include "ColorPickerWidget.h"
#include "ColorSelectorButton.h"
#include "raylib.h"
#include "GameUtils.h"
#include "Playing.h"
#include "GridColorButton.h"
#include "ButtonDefinitions.h"

///------------------------------------------------------------------
constexpr int MAX_COLOR_PER_PAGE = 15;

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

    int amountOfColors = (playing->m_colors.size() < MAX_COLOR_PER_PAGE) ? playing->m_colors.size() - 1 : MAX_COLOR_PER_PAGE;

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
            m_gridColors.push_back(newColor);

            int index = height * 3 + width;
            if (index > amountOfColors)
                break;

            // live updates
            ColorLookup color = ColorToInt(m_playing->m_colors[index]);
            int* intPoint = &playing->m_ColorProgress[color];

            //newColor->Init(m_playing->m_colors[index], index, 69);
            bool isSelectedColor = (index == 0) ? true : false;
            newColor->Init(m_playing->m_colors[index], index, intPoint, isSelectedColor);

            minX += .3;
        }

        minX = .1;
        minY += .2;
    }

    // Next Page tabs 
    m_showPageButtons = m_playing->m_colors.size() > 15;
    if(m_showPageButtons)
    {
        AABB2 previousBounds = GetAABB2FromAABB2({.1,.475}, {.2,.575}, bounds);
        m_previousButton = new ColorSelectorNextPageButton(previousBounds, "<");
        
        AABB2 nextBounds = GetAABB2FromAABB2({ .8,.475 }, { .9,.575 }, bounds);
        m_nextButton = new ColorSelectorNextPageButton(nextBounds, ">");
    }

    m_lastPage = floor(m_playing->m_colors.size() / MAX_COLOR_PER_PAGE);
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

            for (GridColorButton* currentColor : m_gridColors)
            {
                if (currentColor->IsSelected(mousePos))
                {
                    m_playing->m_selected_color = currentColor->m_index;

                    // TODO do something better to turn off the one that was on
                    for(GridColorButton* currentButton : m_gridColors)
                    {
                        currentButton->m_isSelectedColor = false;
                    }

                    currentColor->m_isSelectedColor = true;
                }
            }
        }

        if (m_isOpen == false)
        {

        }
        else
        {

        }

        if (m_showPageButtons)
        {
            if (m_currentPage != 0)
            {
                if (m_previousButton->IsSelected(mousePos))
                {
                    m_currentPage--;
                    UpdateButtonValues();
                }
            }

            if (m_currentPage != m_lastPage)
            {
                if(m_nextButton->IsSelected(mousePos))
                {
                    m_currentPage++;
                    UpdateButtonValues();
                }
            }
        }
    }
}

///------------------------------------------------------------------
void ColorPickerWidget::UpdateButtonValues()
{
    int startingIndex = m_currentPage * MAX_COLOR_PER_PAGE;
    
    for(int i = 0; i < MAX_COLOR_PER_PAGE; i++)
    {
        int index = startingIndex + i;
        
        GridColorButton* currentButton = m_gridColors[i];
        
        // we don't have a color for that button
        if(index >= m_playing->m_colors.size())
        {
            currentButton->m_isVisible = false;
            continue;
        }

        currentButton->m_isVisible = true;

        ColorLookup color = ColorToInt(m_playing->m_colors[index]);
        int* intPoint = &m_playing->m_ColorProgress[color];

        bool isSelectedColor = (m_playing->m_selected_color == index) ? true : false;

        currentButton->Init(m_playing->m_colors[index], index, intPoint, isSelectedColor);
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

    DrawAABB2Filled(m_bounds, BLACK);
    DrawAABB2(m_bounds, WHITE);
    
    
    DrawAABB2(m_headerBounds, WHITE);
    DrawAABB2(m_closeBounds, RED);
    DrawAABB2(m_colorsBounds, WHITE);

    for(GridColorButton* color : m_gridColors)
    {
        color->Render();
    }


    if(m_showPageButtons)
    {
        if(m_currentPage != 0)
        {
            m_previousButton->Render();
        }

        if(m_currentPage != m_lastPage)
        {
            m_nextButton->Render();
        }
    }
}