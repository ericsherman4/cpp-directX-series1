#include "Brick.h"

Brick::Brick()
    :
    rect(RectF(0.0f, 1.0f, 0.0f, 1.0f)),
    c(Colors::White),
    isDestroyed(false)
{
}

Brick::Brick(const RectF & rect, Color c)
    :
    rect(rect),
    c(c),
    isDestroyed(false)
{
}

void Brick::Draw(Graphics& gfx) const
{
    if (!isDestroyed)
    {
        gfx.DrawRect(rect, c);
    }
}

void Brick::SetDestroyed(bool value)
{
    isDestroyed = value;
}

const RectF& Brick::GetRect()
{
    return rect;
}


