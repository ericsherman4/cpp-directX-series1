#pragma once //dont include the file more than once

#include "Graphics.h"
#include "Dude.h"

class Poo
{
	// members in the class default to private if no scope specifier given
public:
	//Poo(int in_x, int in_y, int in_vx, int in_vy);
	void Init(int in_x, int in_y, int in_vx, int in_vy);
	void Update();
	void ProcessConsumption(const Dude &dude);	//make const because not changing any of the member variables of the dude object 
												// we are only reading
	void Draw(Graphics &gfx) const; // make function const if it doesnt alter any member varibales of this class.
	bool IsEaten() const;
private:
	int x;
	int y;
	int vx;
	int vy;
	static constexpr int width = 24; //need constexpr or else it wont work, need it if you want to initialize it in the class like this
	static constexpr int height = 24;
	bool isEaten = false;
	bool initialized = false;

};


