#include "../Include/Vector2.h"


Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}


Vector2::Vector2(int x, int y)
{
	this->x = x;
	this->y = y;
}


Vector2::Vector2(double x, double y)
{
	this->x = x;
	this->y = y;
}


Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}



int Vector2::r()
{
	return this->x;
}


int Vector2::g()
{
	return this->y;
}

