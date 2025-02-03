#include "Attract.h"
#include "Game.h"
#include "UI/ButtonDefinitions.h"

Attract::Attract()
{
    AABB2 UIBounds = g_theGame->m_UIBounds;
    
    AABB2 bounds = GetAABB2FromAABB2({.4, .6}, {.6, .7}, UIBounds);
    m_startButton = new TextButton(bounds, "Start!");
    m_startButton->m_fontSize = 32;
}

Attract::~Attract()
{
    delete m_startButton;
    m_startButton = nullptr;
}

void Attract::OnEnter()
{
}

void Attract::OnExit()
{

}

void Attract::Update(float ds)
{
    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        if(m_startButton->IsSelected(mousePos))
        {
            OnExit();
            g_theGame->m_currentMode = PLAYING;
            g_theGame->m_gameScenes[PLAYING]->OnEnter();
        }
    }
}

void Attract::Render() const
{
    BeginMode2D(g_theGame->m_UICamera);

    AABB2 UIBounds = g_theGame->m_UIBounds;

    Vector2 textPos = UIBounds.GetPositionWithinBox({ .5, .3 });
    int textSize = MeasureText("Caroline's Pixels!", 128);
    DrawText("Caroline's Pixels!", textPos.x - (textSize * .5), textPos.y, 128, PINK);

    m_startButton->Render();

    EndMode2D();
}
