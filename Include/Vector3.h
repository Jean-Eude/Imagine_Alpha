#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "Vector2.h"

class Vector3
{
public:

int x,y,z;

Vector3(int x, int y, int z);
Vector3(double x, double y, double z);
Vector3(float x, float y, float z);
Vector3(Vector2 vec, int z);
Vector3(Vector2 vec, double z);
Vector3(Vector2 vec, float z);


// Getteurs 

int r();
int g();
int b();


};


#endif