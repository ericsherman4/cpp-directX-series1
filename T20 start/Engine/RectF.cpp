#include "RectF.h"

RectF::RectF()
    :
    top(0),
    left(0),
    bottom(0),
    right(0)
{
}

RectF::RectF(float top, float left, float bottom, float right)
    :
    top(top),
    left(left),
    bottom(bottom),
    right(right)
{
}

RectF::RectF(const Vec2& topleft, const Vec2& bottomright)
    :
    RectF(topleft.y, topleft.x, bottomright.y, bottomright.x)

{
}

RectF::RectF(const Vec2& topleft, float width, float height)
    : 
    RectF(topleft, Vec2(width, height))
{
    
}

RectF RectF::createRectFromCenter(const Vec2& center, float halfwidth, float halfheight)
{
    const Vec2 half(halfwidth, halfheight);
    return RectF(center - half, center + half);
}

bool RectF::isOverlapping(const RectF& rect) const
{
    //if (rect.top < bottom)
    //{
    //    if (bottom < rect.top < right)
    //    {
    //        return true;
    //    }
    //    if (bottom < rect.left < right)
    //    {
    //        return true;
    //    }
    //}
    //else if (rect.bottom > top)
    //{
    //    if (top < rect.bottom < left)
    //    {
    //        return true;
    //    }
    //    if (top < rect.right < left)
    //    {
    //        return true;
    //    }
    //}
    
    // ball is rect - top, left, bottom right is the brick (this)
    if (rect.top < bottom && left < rect.right && rect.left < right && rect.bottom > top)
    {
        return true;
    }

    
    return false;
}






