#pragma once
#include "AABB2.h"

///------------------------------------------------------------------
struct Vector2;

///------------------------------------------------------------------
class Widget
{
public:
    Widget(AABB2& bounds)
    {
        m_bounds = bounds;
    }

public:
    virtual void Update(float ds) {};
    virtual void Render() const {};

    virtual bool IsSelected(Vector2& mousePos) const;

public:
    AABB2   m_bounds;
    bool    m_isVisible = true;
};