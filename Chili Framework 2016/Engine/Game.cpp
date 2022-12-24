/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes?redirectedfrom=MSDN
	
	const int offset = 1;

	// change color
	if (wnd.kbd.KeyIsPressed (VK_CONTROL))
	{
		color = 255;
	}
	else
	{
		color = 0;
	}

	//change shape
	if (wnd.kbd.KeyIsPressed(VK_SHIFT))
	{
		shapeChanged = true;
	}
	else
	{
		shapeChanged = false;
	}

	//update velocities
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		if (!inhibitUp)
		{
			vy = vy - offset;
			inhibitUp = true;
		}
	}
	else
	{
		inhibitUp = false;
	}

	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		if (!inhibitRight)
		{
			vx = vx + offset;
			inhibitRight = true;
		}
	}
	else
	{
		inhibitRight = false;
	}

	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		if (!inhibitLeft)
		{
			vx = vx - offset;
			inhibitLeft = true;
		}	
	}
	else
	{
		inhibitLeft = false;
	}

	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		if (!inhibitDown)
		{
			vy = vy + offset;
			inhibitDown = true;
		}
	}
	else
	{
		inhibitDown = false;
	}

	//update positions
	x = x + vx;
	y = y + vy;

	//check positiions
	if (x + 5 > gfx.ScreenWidth - 1)
	{
		x = gfx.ScreenWidth - 6;
		vx = 0;
	}
	else if (x - 5 < 0)
	{
		x = 5;
		vx = 0;
	}

	if (y + 5 > gfx.ScreenHeight - 1)
	{
		y = gfx.ScreenHeight - 6;
		vy = 0;
	}
	else if (y - 5 < 0)
	{
		y = 5;
		vy = 0;
	}

	if (x < 412 && x > 388 && y < 312 && y > 288)
	{
		color = 255;
	}
}

void Game::ComposeFrame()
{
	
	if (shapeChanged)
	{
		gfx.PutPixel(x - 5, y, 255, color, color);
		gfx.PutPixel(x - 4, y, 255, color, color);
		gfx.PutPixel(x - 3, y, 255, color, color);
		gfx.PutPixel(x + 3, y, 255, color, color);
		gfx.PutPixel(x + 4, y, 255, color, color);
		gfx.PutPixel(x + 5, y, 255, color, color);
								   
		gfx.PutPixel(x, y - 5, 255, color, color);
		gfx.PutPixel(x, y - 4, 255, color, color);
		gfx.PutPixel(x, y - 3, 255, color, color);
		gfx.PutPixel(x, y + 3, 255, color, color);
		gfx.PutPixel(x, y + 4, 255, color, color);
		gfx.PutPixel(x, y + 5, 255, color, color);
	}
	else
	{

		gfx.PutPixel(x - 6, y - 6, 255, color, color);
		gfx.PutPixel(x - 5, y - 6, 255, color, color);
		gfx.PutPixel(x - 4, y - 6, 255, color, color);
		gfx.PutPixel(x - 3, y - 6, 255, color, color);
		gfx.PutPixel(x - 6, y - 5, 255, color, color);
		gfx.PutPixel(x - 6, y - 4, 255, color, color);
		gfx.PutPixel(x - 6, y - 3, 255, color, color);

		gfx.PutPixel(x + 6, y - 6, 255, color, color);
		gfx.PutPixel(x + 5, y - 6, 255, color, color);
		gfx.PutPixel(x + 4, y - 6, 255, color, color);
		gfx.PutPixel(x + 3, y - 6, 255, color, color);
		gfx.PutPixel(x + 6, y - 5, 255, color, color);
		gfx.PutPixel(x + 6, y - 4, 255, color, color);
		gfx.PutPixel(x + 6, y - 3, 255, color, color);

		gfx.PutPixel(x + 6, y + 6, 255, color, color);
		gfx.PutPixel(x + 5, y + 6, 255, color, color);
		gfx.PutPixel(x + 4, y + 6, 255, color, color);
		gfx.PutPixel(x + 3, y + 6, 255, color, color);
		gfx.PutPixel(x + 6, y + 5, 255, color, color);
		gfx.PutPixel(x + 6, y + 4, 255, color, color);
		gfx.PutPixel(x + 6, y + 3, 255, color, color);

		gfx.PutPixel(x - 6, y + 6, 255, color, color);
		gfx.PutPixel(x - 5, y + 6, 255, color, color);
		gfx.PutPixel(x - 4, y + 6, 255, color, color);
		gfx.PutPixel(x - 3, y + 6, 255, color, color);
		gfx.PutPixel(x - 6, y + 5, 255, color, color);
		gfx.PutPixel(x - 6, y + 4, 255, color, color);
		gfx.PutPixel(x - 6, y + 3, 255, color, color);


		//gfx.PutPixel(x - 5, y, 255, color, color);
		//gfx.PutPixel(x - 4, y, 255, color, color);
		//gfx.PutPixel(x - 3, y, 255, color, color);
		//gfx.PutPixel(x - 2, y, 255, color, color);
		//gfx.PutPixel(x - 1, y, 255, color, color);
		//gfx.PutPixel(x - 0, y, 255, color, color);
		//gfx.PutPixel(x + 1, y, 255, color, color);
		//gfx.PutPixel(x + 2, y, 255, color, color);
		//gfx.PutPixel(x + 3, y, 255, color, color);
		//gfx.PutPixel(x + 4, y, 255, color, color);
		//gfx.PutPixel(x + 5, y, 255, color, color);

		//gfx.PutPixel(x, y - 5, 255, color, color);
		//gfx.PutPixel(x, y - 4, 255, color, color);
		//gfx.PutPixel(x, y - 3, 255, color, color);
		//gfx.PutPixel(x, y - 2, 255, color, color);
		//gfx.PutPixel(x, y - 1, 255, color, color);
		//gfx.PutPixel(x, y + 0, 255, color, color);
		//gfx.PutPixel(x, y + 1, 255, color, color);
		//gfx.PutPixel(x, y - 2, 255, color, color);
		//gfx.PutPixel(x, y + 3, 255, color, color);
		//gfx.PutPixel(x, y + 4, 255, color, color);
		//gfx.PutPixel(x, y + 5, 255, color, color);
	}

	gfx.PutPixel(400 - 6, 300 - 6, 0, 255, 0);
	gfx.PutPixel(400 - 5, 300 - 6, 0, 255, 0);
	gfx.PutPixel(400 - 4, 300 - 6, 0, 255, 0);
	gfx.PutPixel(400 - 3, 300 - 6, 0, 255, 0);
	gfx.PutPixel(400 - 6, 300 - 5, 0, 255, 0);
	gfx.PutPixel(400 - 6, 300 - 4, 0, 255, 0);
	gfx.PutPixel(400 - 6, 300 - 3, 0, 255, 0);
	gfx.PutPixel(400 + 6, 300 - 6, 0, 255, 0);
	gfx.PutPixel(400 + 5, 300 - 6, 0, 255, 0);
	gfx.PutPixel(400 + 4, 300 - 6, 0, 255, 0);
	gfx.PutPixel(400 + 3, 300 - 6, 0, 255, 0);
	gfx.PutPixel(400 + 6, 300 - 5, 0, 255, 0);
	gfx.PutPixel(400 + 6, 300 - 4, 0, 255, 0);
	gfx.PutPixel(400 + 6, 300 - 3, 0, 255, 0);
	gfx.PutPixel(400 + 6, 300 + 6, 0, 255, 0);
	gfx.PutPixel(400 + 5, 300 + 6, 0, 255, 0);
	gfx.PutPixel(400 + 4, 300 + 6, 0, 255, 0);
	gfx.PutPixel(400 + 3, 300 + 6, 0, 255, 0);
	gfx.PutPixel(400 + 6, 300 + 5, 0, 255, 0);
	gfx.PutPixel(400 + 6, 300 + 4, 0, 255, 0);
	gfx.PutPixel(400 + 6, 300 + 3, 0, 255, 0);
	gfx.PutPixel(400 - 6, 300 + 6, 0, 255, 0);
	gfx.PutPixel(400 - 5, 300 + 6, 0, 255, 0);
	gfx.PutPixel(400 - 4, 300 + 6, 0, 255, 0);
	gfx.PutPixel(400 - 3, 300 + 6, 0, 255, 0);
	gfx.PutPixel(400 - 6, 300 + 5, 0, 255, 0);
	gfx.PutPixel(400 - 6, 300 + 4, 0, 255, 0);
	gfx.PutPixel(400 - 6, 300 + 3, 0, 255, 0);
}

void Game::DrawBox()
{

}
