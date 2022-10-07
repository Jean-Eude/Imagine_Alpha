#include "../Include/Headers.h"
#include "../Include/MathFunc.h"



// Implémentation de certaines fonctions mathématiques utiles.


float clamp(float x, float min, float max)
{ 
	if(x < min)
	{
		x = min;
	}
	else if(x > max)
	{
		x = max;
	}
	return x;
}


float step(float a, float x)   // Heaviside step function -> soit 1 ou 0 et pas 255 ou 0.
{
  if(a < x)
  {
  	return 1.0;
  }
  
  return 0.0;
}


float smoothStep(float edge0, float edge1, float x)
{
	x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);

	return x * x * x * (x * (x * 6 - 15) + 10);
}


float invSmoothstep(float x)
{
	return 0.5 - sin(asin(1.0 - 2.0 * x) / 3.0);
}


// Linear interpolation between(aColor, bColor, third that decide if its the a or b color to piut in the pixel).
float lerp(float v0, float v1, float t) // == mix()
{
  return (1.0 - t) * v0 + t * v1; // -> soit 1 ou 0 et pas 255 ou 0.
}


float min(float a, float b)
{
	if(a < b)
	{
		return a;
	}
	
	return b;
}


float max(float a, float b)
{
	if(a > b)
	{
		return a;
	}
	
	return b;
}


float length(float x, float y, float z)
{
	return sqrt(x*x + y*y + z*z);
}


float normalize(float channel_input)
{
	return 255 * (channel_input - 0 / 255 - 0);
}

int truncate(int value)  // == fonction clamp mais avec un seul paramètre
{
	int ret = value;

  if(ret < 0)
  {
   	ret = 0;
  }  
  else if(ret > 255)
  {
   	ret = 255;
  }
   
  return ret;
}