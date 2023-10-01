#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"

class Brick
{
public:
    Brick();
    Brick(const RectF &rect, Color c);
    void Draw(Graphics& gfx) const;
    void SetDestroyed(bool value);
    bool GetDestroyed() const;
    const RectF& GetRect();

private:
    RectF rect;
    Color c;
    bool isDestroyed;
};

