#include "Target.h"

Target::Target()
    :
    rng(rd()),
    xDist(0,800-width-1),
    yDist(0,600-width-1)
   
{
    x = xDist(rng);
    y = yDist(rng);
}

bool Target::ProcessCollision(const Dude& dude)
{

    // conditions
    // dude right >= target left (x)
    // dude left (x) <= target right
    // dude bottom >= target top (y)
    // dude top (y) <= target bottom 

    const int dudeRight = dude.GetXPos() + dude.GetWidth();
    const int dudeBottom = dude.GetYPos() + dude.GetHeight();
    const int targetRight = x + width;
    const int targetBottom = y + height;


    if (dudeRight >= x && dude.GetXPos() <= targetRight && dudeBottom >= y && dude.GetYPos() <= targetBottom)
    {
        return true;
    }

    return false;
    
}

void Target::Move()
{
    x = xDist(rng);
    y = yDist(rng);
}

void Target::UpdateColors()
{
    if (colorflip)
    {
        green += colorspeed;
        blue += colorspeed;
    }
    else {
        green -= colorspeed;
        blue -= colorspeed;
    }

    if (green >= 255 || green <= 0)
    {
        colorflip = !colorflip;
    }

    if (green > 255)
    {
        green = 255;
        blue = 255;
    }

    if (green < 0)
    {
        green = 0;
        blue = 0;
    }
    
}


void Target::Draw(Graphics & gfx)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gfx.PutPixel(x+i, y+j, red, green, blue);
        }
    }
}
