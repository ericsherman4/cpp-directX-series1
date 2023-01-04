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
        nSegments++;
    }
}

void Snake::Draw(Board& brd) const
{
    for (int i = 0; i < nSegments; i++)
    {
        segments[i].Draw(brd);
    }
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
    brd.DrawCell(loc, c);
}
