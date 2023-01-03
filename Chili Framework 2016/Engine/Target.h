#pragma once

#include "Dude.h"
#include "Graphics.h"
#include <random>

class Target
{
public:
    Target();
    bool ProcessCollision(const Dude& dude);
    void Move();
    void Draw(Graphics & gfx);
    void UpdateColors();


private:
    std::random_device rd;
    std::mt19937 rng;
    std::uniform_int_distribution<int> xDist;
    std::uniform_int_distribution<int> yDist;


    static constexpr int width = 20;
    static constexpr int height = 20;
    static constexpr int colorspeed = 3;
    int x; //these will represent the top left corner of it
    int y;
    int red = 255;
    int green = 0;
    int blue = 0;
    bool colorflip = true;
};

