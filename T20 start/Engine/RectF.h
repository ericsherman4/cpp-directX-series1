#pragma once

#include "Vec2.h"

class RectF
{
public:

    RectF();
    RectF(float top, float left, float bottom, float right);
    RectF(const Vec2& topleft, const Vec2& bottomright);
    RectF(const Vec2& topleft, float width, float height);
    static RectF createRectFromCenter(const Vec2& center, float halfwidth, float halfheight);

    bool isOverlapping(const RectF &rect) const;
    
    float top;
    float right;
    float left;
    float bottom;

private:
};

