#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& loc)
{
    segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location& delta_loc)
{
    for (int i = nSegments - 1; i > 0; i--)
    {
        segments[i].Follow(segments[i-1]);
    }
    segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
    if (nSegments < nSegmentsMax-1)
    {
        segments[nSegments++].InitBody();
    }
}

void Snake::Draw(Board& brd) const
{
    for (int i = 0; i < nSegments; i++)
    {
        segments[i].Draw(brd);
    }
}

Location Snake::GetHeadLoc()
{
    return segments[0].GetLoc();
}

bool Snake::CheckSelfCollision()
{
    Location headloc = segments[0].GetLoc();
    for (int i = 1; i < nSegments; i++)
    {
        if (headloc.x == segments[i].GetLoc().x && headloc.y == segments[i].GetLoc().y)
        {
            return true;
        }
    }
    return false;
}

bool Snake::IsInBounds(const Board& brd)
{
    Location headloc = GetHeadLoc();
    return headloc.x <= brd.GetGridWidth() && headloc.x >= 0 && headloc.y <= brd.GetGridHeight() && headloc.y >= 0;
}

void Snake::Segment::InitHead(const Location& in_loc)
{
    loc = in_loc; //calls default copy constructor
    c = Snake::headColor; //you can access it even though its private because Segment is also private to Snake
}

void Snake::Segment::InitBody()
{
    c = Snake::bodyColor;
}

void Snake::Segment::Follow(const Segment& next)
{
    loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
    // ensure that the snake is only moved by one pixel at a time.
    assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);

    loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board& brd) const
{
    if (loc.x >= 0 && loc.x <= brd.GetGridWidth() && loc.y >= 0 && loc.y <= brd.GetGridHeight())
    {
        brd.DrawCell(loc, c);
    }
}

Location Snake::Segment::GetLoc()
{
    return loc;
}
