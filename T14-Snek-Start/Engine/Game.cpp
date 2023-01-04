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
#include "SpriteCodex.h"



Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()), //the first set of parenthesis calls the constructor to create the engine. the 2nd set is an overloaded operator () and this advances the engine's state and returns the generated value. see https://en.cppreference.com/w/cpp/numeric/random/random_device.
	snek(snakeStartLoc),
	target(targetStartLoc,brd, Colors::Red)
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
	if (!isGameOver) {
		if (wnd.kbd.KeyIsPressed('W'))
		{
			snakeDir.Set(0, -1);
		}
		if (wnd.kbd.KeyIsPressed('D'))
		{
			snakeDir.Set(1, 0);
		}
		if (wnd.kbd.KeyIsPressed('A'))
		{
			snakeDir.Set(-1, 0);
		}
		if (wnd.kbd.KeyIsPressed('S'))
		{
			snakeDir.Set(0, 1);
		}

		if (++speedInhibit % snakeSpeed == 0)
		{
			if (target.CheckCollision(snek.GetHeadLoc()))
			{
				snek.Grow();
				snek.Grow();
				snek.Grow();
				target.Move();
			}
			if (snek.CheckSelfCollision() || !snek.IsInBounds(brd))
			{
				isGameOver = true;
			}
			snek.MoveBy(snakeDir);
		}
	}
}

void Game::ComposeFrame()
{
	// std::uniform_int_distribution<int> colorDist(0, 255); //move this
	for (int y = 0; y < brd.GetGridHeight(); y++)
	{
		for (int x = 0; x < brd.GetGridWidth(); x++)
		{
			// Color c(colorDist(rng), colorDist(rng), colorDist(rng));
			const int color = 50;
			Color c(color, color, color);
			Location loc = { x,y }; // can only do this if there is no private data and no constructors.
			brd.DrawCell(loc, c);
		}
	}
	snek.Draw(brd);
	target.Draw(brd);
	
	if (isGameOver)
	{
		SpriteCodex::DrawGameOver(350,300, gfx);
	}

}
