#pragma once

#include "Graphics.h"

class Dude
{
public:
	void Update();
	void Draw(Graphics &gfx) const;

	int x;
	int y;
	static constexpr int width = 20;
	static constexpr int height = 20;
};

