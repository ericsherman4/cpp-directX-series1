#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
    Board(Graphics& gfx);
    void DrawCell(Location & loc, Color c);
    int GetGridWidth() const;
    int GetGridHeight() const;
private:
    static constexpr int dimension = 20; //dimensions of the cells in the board. cells are 20x20
    static constexpr int width = 10; //width and height of the board, this is number of cells, not pixels.
    static constexpr int height = 10; 
    Graphics& gfx;
};

