#pragma once

#include "Graphics.h"
#include "Keyboard.h"

class Dude
{
public:
	Dude(int in_x, int in_y);
	void Update();
	void Draw(Graphics &gfx) const;
	void CheckKeys(const Keyboard& kbd);
	int GetXPos() const;
	int GetYPos() const;
	int GetWidth() const;
	int GetHeight() const;

private:
	int x;
	int y;
	static constexpr int width = 20;
	static constexpr int height = 20;
	static constexpr int speed = 2;
};

