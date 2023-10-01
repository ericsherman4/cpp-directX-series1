#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>




class Board
{
public:
	Board( Graphics& gfx );
	void DrawCell( const Location& loc,Color c );
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard( const Location& loc ) const;
	bool checkForObstacle(const Location& loc) const;
	void DrawBorder();
	// forward declaration!
	void SpawnObstacle(std::mt19937& rng, const class Snake& snake, const class Goal & goal);
	void DrawObstacles();
private:
	static constexpr Color borderColor = Colors::Blue;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr int dimension = 20;
	static constexpr int cellPadding = 1;
	static constexpr int width = 32;
	static constexpr int height = 24;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;
	static constexpr int x = 70;
	static constexpr int y = 50;
	bool hasObstacle[width * height] = { false }; // intialize everything to false
	Graphics& gfx;
};