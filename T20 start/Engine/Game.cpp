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
#include "Vec2.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ball(Vec2(400.0f,300.0f), Vec2(300.0f,400.134f)),
	walls(0.0f, 0.0f, float(gfx.ScreenHeight), float(gfx.ScreenWidth))
	// RectF(float top, float left, float bottom, float right)
	//walls(RectF(300, 300, 500, 500))
{
	const Color colors[rows] = { Colors::Red, Colors::White, Colors::Blue, Colors::Green, Colors::Cyan };

	Vec2 topleft(startx, starty);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			bricks[i*cols + j] = Brick(RectF(topleft, brickwidth, brickheight), colors[i]);
			topleft.x += brickwidth + spacex;
		}
		topleft.x = startx;
		topleft.y += brickheight + spacey;
	}

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
	const float dt = ft.Mark();
	//const float frametime = 1.0f / 60.0f;
	ball.Update(dt);
	ball.handleWallCollision(walls);


	for (Brick& b : bricks)
	{
		if (!b.GetDestroyed())
		{
			bool destroyed = ball.handleBrickCollision(b.GetRect());
			b.SetDestroyed(destroyed);
			if (destroyed)
			{
				break;
			}
		}
	}


}

void Game::ComposeFrame()
{
	gfx.DrawRect(walls, Colors::Black);

	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}

	ball.Draw(gfx);
}
