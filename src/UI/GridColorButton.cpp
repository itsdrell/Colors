#include "GridColorButton.h"
#include "GameUtils.h"
#include <string>

void GridColorButton::Render() const
{
    if(*m_amountLeftPointer <= 0)
    {
        return;
    }
    
    DrawAABB2Filled(m_bounds, m_color);

    std::string numberIndex = std::to_string(m_index);
    Vector2 indexTextPos = m_bounds.GetPositionWithinBox({ .4,.4 });
    DrawText(numberIndex.c_str(), indexTextPos.x, indexTextPos.y, 16, WHITE);

    AABB2 numberBox = GetAABB2FromAABB2({0, .8}, {1, 1}, m_bounds);
    DrawAABB2Filled(numberBox, WHITE);
    
    std::string progressText = std::to_string(*m_amountLeftPointer);
    Vector2 progressTextPos = numberBox.GetPositionWithinBox({ .1,.3 });
    DrawText(progressText.c_str(), progressTextPos.x, progressTextPos.y, 12, BLACK);
    
    DrawAABB2(m_bounds, WHITE);
}
