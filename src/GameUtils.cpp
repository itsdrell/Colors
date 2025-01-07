#include "GameUtils.h"
#include "AABB2.h"
#include "raylib.h"
#include <cstdlib>

void DrawAABB2(const AABB2& bounds, Color& theColor)
{
    DrawRectangleLines( bounds.mins.x,
                        bounds.mins.y,
                        abs(bounds.maxs.x - bounds.mins.x),
                        abs(bounds.maxs.y - bounds.mins.y),
                        theColor);
}

