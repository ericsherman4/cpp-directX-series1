#include "Target.h"

Target::Target(const Location& loc, const Board& brd ,Color c)
    :
    loc (loc),
    c (c),
    rng(std::random_device()()),
    rowDist(0,brd.GetGridWidth()),
    colDist(0,brd.GetGridHeight())
{
}

void Target::Move()
{
    loc.Set(rowDist(rng), colDist(rng));
}

void Target::Draw(Board & brd) const
{
    brd.DrawCell(loc, c);
}

bool Target::CheckCollision(const Location& in_loc) const
{
    return loc.x == in_loc.x && loc.y == in_loc.y;
}
