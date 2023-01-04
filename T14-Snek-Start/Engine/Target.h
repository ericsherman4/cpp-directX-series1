#pragma once

#include "Colors.h"
#include "Board.h"
#include "Location.h"
#include <random>

class Target
{
public:
    Target(const Location & loc, const Board& brd, Color c);
    void Move();
    void Draw(Board & brd) const;
    bool CheckCollision(const Location & in_loc) const;
private:
    Location loc;
    Color c; 
    std::mt19937 rng;
    std::uniform_int_distribution<> rowDist;
    std::uniform_int_distribution<> colDist;

};

