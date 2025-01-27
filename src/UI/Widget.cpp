#include "Widget.h"

bool Widget::IsSelected(Vector2& mousePos) const
{
    return m_bounds.IsPointInBox(mousePos);
}

