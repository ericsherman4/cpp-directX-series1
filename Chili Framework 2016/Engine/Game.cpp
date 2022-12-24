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
}

void Game::ComposeFrame()
{
	int x = 400;
	int y = 300;

	// shift control space to view definition
	// vk = virtual key (code)
	// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes?redirectedfrom=MSDN
	// const bool cond = wnd.kbd.KeyIsPressed( VK_UP ); 
	

	const bool symboltype = wnd.kbd.KeyIsPressed( VK_SHIFT );
	const bool color = wnd.kbd.KeyIsPressed( VK_CONTROL );
	int color1 = 0;
	int color2 = 0;

	if (color)
	{
		color1 = 255;
	}
	else
	{
		color2 = 255;
	}

	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		y = y - 50;
	}

	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		x = x + 50;
	}

	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		x = x - 50;
	}

	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		y = y + 50;
	}

	if (!symboltype)
	{
		gfx.PutPixel(x - 5, y, 0, color1, color2);
		gfx.PutPixel(x - 4, y, 0, color1, color2);
		gfx.PutPixel(x - 3, y, 0, color1, color2);
		gfx.PutPixel(x + 3, y, 0, color1, color2);
		gfx.PutPixel(x + 4, y, 0, color1, color2);
		gfx.PutPixel(x + 5, y, 0, color1, color2);

		gfx.PutPixel(x, y - 5, 0, color1, color2);
		gfx.PutPixel(x, y - 4, 0, color1, color2);
		gfx.PutPixel(x, y - 3, 0, color1, color2);
		gfx.PutPixel(x, y + 3, 0, color1, color2);
		gfx.PutPixel(x, y + 4, 0, color1, color2);
		gfx.PutPixel(x, y + 5, 0, color1, color2);
	}
	else
	{
		gfx.PutPixel(x - 5, y, 0, color1, color2);
		gfx.PutPixel(x - 4, y, 0, color1, color2);
		gfx.PutPixel(x - 3, y, 0, color1, color2);
		gfx.PutPixel(x - 2, y, 0, color1, color2);
		gfx.PutPixel(x - 1, y, 0, color1, color2);
		gfx.PutPixel(x - 0, y, 0, color1, color2);
		gfx.PutPixel(x + 1, y, 0, color1, color2);
		gfx.PutPixel(x + 2, y, 0, color1, color2);
		gfx.PutPixel(x + 3, y, 0, color1, color2);
		gfx.PutPixel(x + 4, y, 0, color1, color2);
		gfx.PutPixel(x + 5, y, 0, color1, color2);

		gfx.PutPixel(x, y - 5, 0, color1, color2);
		gfx.PutPixel(x, y - 4, 0, color1, color2);
		gfx.PutPixel(x, y - 3, 0, color1, color2);
		gfx.PutPixel(x, y - 2, 0, color1, color2);
		gfx.PutPixel(x, y - 1, 0, color1, color2);
		gfx.PutPixel(x, y + 0, 0, color1, color2);
		gfx.PutPixel(x, y + 1, 0, color1, color2);
		gfx.PutPixel(x, y - 2, 0, color1, color2);
		gfx.PutPixel(x, y + 3, 0, color1, color2);
		gfx.PutPixel(x, y + 4, 0, color1, color2);
		gfx.PutPixel(x, y + 5, 0, color1, color2);
	}
}
