#include "ButtonDefinitions.h"
#include "GameUtils.h"

///------------------------------------------------------------------
void ColorSelectorNextPageButton::Render() const
{
    DrawAABB2Filled(m_bounds, LIGHTGRAY);

    Vector2 pos = m_bounds.GetPositionWithinBox({ .5,.5 });
    DrawText(m_displayText.c_str(), pos.x, pos.y, 16, WHITE);
}

///------------------------------------------------------------------
void TextButton::Render() const
{
    DrawAABB2Filled(m_bounds, LIGHTGRAY);

    Vector2 pos = m_bounds.GetPositionWithinBox({ .5,.5 });
    int textSize = MeasureText(m_displayText.c_str(), m_fontSize);

    DrawText(m_displayText.c_str(), pos.x - (textSize * .5), pos.y, m_fontSize, WHITE);
}
