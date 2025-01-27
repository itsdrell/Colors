#include "ColorSelectorButton.h"
#include "GameUtils.h"

void ColorSelectorButton::Render() const
{
    DrawAABB2(m_bounds, WHITE);
}

bool ColorSelectorButton::OnClicked()
{
    return false;
}
