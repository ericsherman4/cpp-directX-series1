#include "Ball.h"

#include "SpriteCodex.h"


Ball::Ball()
    :
    pos(Vec2(0, 0)),
    vel(Vec2(0, 0))
{
}

Ball::Ball(const Vec2& pos, const Vec2& vel)
    :
    pos(pos),
    vel(vel)
{
}

void Ball::Draw(Graphics& gfx) const
{
    SpriteCodex::DrawBall(pos, gfx);
}

RectF Ball::GetRect(void) const
{
    return RectF::createRectFromCenter(pos, radius, radius);
}

void Ball::Update(const float dt)
{
    pos += vel * dt;
}

bool Ball::handleWallCollision(const RectF& rect_in)
{
    bool collided = false;
    // passed right border
    if ((pos.x + radius) > rect_in.right)
    {
        //pos.x = pos.x - (pos.x + radius - rect_in.left);
        pos.x = rect_in.right - radius;
        ReboundX();
        collided = true;
    }
    else if ((pos.x - radius) < rect_in.left)
    {
        pos.x = rect_in.left + radius;
        ReboundX();
        collided = true;
    }

    if ((pos.y + radius) > rect_in.bottom)
    {
        pos.y = rect_in.bottom - radius;
        ReboundY();
        collided = true;
    }
    else if ((pos.y - radius) < rect_in.top)
    {
        pos.y = rect_in.top + radius;
        ReboundY();
        collided = true;
    }
    return collided;
}

bool Ball::handleBrickCollision(const RectF& rect_in)
{
    const RectF ball_rect = Ball::GetRect();
    if (!ball_rect.isOverlapping(rect_in))
    {
        return false;
    }

    float min_deflection = 999999999.0f;
    int identifier = 0;

    // Find the closest edge to the collision spot and store it

    if (abs(ball_rect.bottom - rect_in.top) < min_deflection)
    {
        min_deflection = abs(ball_rect.bottom - rect_in.top);
        identifier = 0;
    }

    if (abs(ball_rect.top - rect_in.bottom) < min_deflection)
    {
        min_deflection = abs(ball_rect.top - rect_in.bottom);
        identifier = 1;
    }
  
    if (abs(rect_in.right - ball_rect.left) < min_deflection)
    {
        min_deflection = abs(rect_in.right - ball_rect.left);
        identifier = 2;
    }

    if (abs(ball_rect.right - rect_in.left) < min_deflection)
    {
        min_deflection = (ball_rect.right - rect_in.left);
        identifier = 3;
    }

    // Based on that edge, apply the position offset to move the ball
    // out of the rectangle it collided with. then reflect vel.
    switch (identifier)
    {
        case 0:
            pos.y -= min_deflection;
            ReboundY();
            break;
        case 1:
            pos.y += min_deflection;
            ReboundY();
            break;
        case 2:
            pos.x += min_deflection;
            ReboundX();
            break;
        case 3:
            pos.x -= min_deflection;
            ReboundX();
            break;
    }

    return true;
}


