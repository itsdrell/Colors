#include "GameUtils.h"
#include "AABB2.h"
#include "raylib.h"
#include <cstdlib>

void DrawAABB2(const AABB2& bounds, const Color& theColor)
{
    DrawRectangleLines( bounds.mins.x,
                        bounds.mins.y,
                        abs(bounds.maxs.x - bounds.mins.x),
                        abs(bounds.maxs.y - bounds.mins.y),
                        theColor);
}

void DrawAABB2Filled(const AABB2& bounds, const Color& theColor)
{
    DrawRectangle(bounds.mins.x,
        bounds.mins.y,
        abs(bounds.maxs.x - bounds.mins.x),
        abs(bounds.maxs.y - bounds.mins.y),
        theColor);
}

Color GetRandomColor()
{
    Color colors[25] =
    {
        LIGHTGRAY,GRAY,DARKGRAY,YELLOW,
        GOLD,ORANGE,PINK,RED,MAROON,
        GREEN,LIME,DARKGREEN,SKYBLUE,
        BLUE,DARKBLUE,PURPLE,VIOLET,
        DARKPURPLE,BEIGE,BROWN,DARKBROWN,
        WHITE,BLACK,MAGENTA,RAYWHITE
    };

    int index = GetRandomValue(0, 24);
    return colors[index];
}         