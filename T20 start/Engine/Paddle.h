#pragma once

#include "RectF.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Vec2.h"

class Paddle
{
public:
    void Draw(Graphics& gfx);
    void Update(const Keyboard& keyboard);


private:
    RectF rect;
    Vec2 pos;

};

