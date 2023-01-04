#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
    Board(Graphics& gfx);
    void DrawCell(const Location & loc, Color c);
    int GetGridWidth() const;
    int GetGridHeight() const;
private:
    static constexpr int dimension = 10; //dimensions of the cells in the board. cells are dim x dim pixels
    static constexpr int width = 80; //width and height of the board, this is number of cells, not pixels.
    static constexpr int height = 60; 
    Graphics& gfx;
};

