#pragma once

#include "Graphics.h"
#include "RectF.h"
#include "Brick.h"

class Ball
{
public:
    Ball();
    Ball(const Vec2& pos, const Vec2& vel);
    void Draw(Graphics& gfx) const;
    RectF GetRect(void) const;
    void Update(const float dt);
    bool handleWallCollision(const RectF& rect_in);
    bool handleBrickCollision(const RectF& rect_in);

    void inline Ball::ReboundX() { vel.x = -vel.x; }
    void inline Ball::ReboundY() { vel.y = -vel.y; }

private:

    static constexpr float radius = 7.0f;
    Vec2 pos;
    Vec2 vel;
};

