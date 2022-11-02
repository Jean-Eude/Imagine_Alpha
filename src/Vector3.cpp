#include "../Include/Vector3.h"

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}



Vector3::Vector3(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Vector3::Vector3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Vector3::Vector3(Vector2 vec, int z)
{
	vec.x = x;
	vec.y = y;
	this->z = z;
}


Vector3::Vector3(Vector2 vec, double z)
{
	vec.x = x;
	vec.y = y;
	this->z = z;
}


Vector3::Vector3(Vector2 vec, float z)
{
	vec.x = x;
	vec.y = y;
	this->z = z;
}


int Vector3::r()
{
	return this->x;
}


int Vector3::g()
{
	return this->y;
}


int Vector3::b()
{
	return this->z;
}
