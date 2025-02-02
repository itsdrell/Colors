#pragma once

//-----------------------------------------------------------------------------------------------
class AABB2;
struct Color;
struct Texture;

//-----------------------------------------------------------------------------------------------
void DrawAABB2(const AABB2& bounds, const Color& theColor);
void DrawAABB2Filled(const AABB2& bounds, const Color& theColor);
void DrawTexturedBox(const Texture& texture, const AABB2& bounds);

Color GetRandomColor();