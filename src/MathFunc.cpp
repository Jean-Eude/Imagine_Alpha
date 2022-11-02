#include "../Include/Headers.h"
#include "../Include/MathFunc.h"



// Implémentation de certaines fonctions mathématiques utiles.

// Basic Functions

double clamp(double x, double min, double max)
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

double step(double a, double x)   // Heaviside step function -> soit 1 ou 0 et pas 255 ou 0.
{
  if(a < x)
  {
  	return 1.0;
  }
  
  return 0.0;
}

double smoothstep(double edge0, double edge1, double x) // --> [0,1]
{
	x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);

	return x * x * (3.0 - 2.0 * x);
}

// Linear interpolation between(aColor, bColor, third that decide if its the a or b color to put in the pixel).
double lerp(double v0, double v1, double t) // == mix()
{
  return (1.0 - t) * v0 + t * v1; // -> soit 1 ou 0 et pas 255 ou 0.
}

double min(double a, double b)
{
	if(a < b)
	{
		return a;
	}
	
	return b;
}

double max(double a, double b)
{
	if(a > b)
	{
		return a;
	}
	
	return b;
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

double mod(double x, double a)
{
	return (x - a) * floor(x/a);
}

double fract(double x) 
{
  return x-(long)x;
}

double sign(double x) 
{
  if(x > 0.0)
  {
  	return -1.;
  }
  else if(x == 0.)
  {
  	return 0.;
  }
  else
  {
  	return 1.;
  }
}


// Advanced Functions --> https://iquilezles.org/articles/functions/

double sinc(double x, double k )			// x,k -> [0,1]
{
    double a = M_PI*(k*x-1.0);
    return sin(a)/a;
}

double pcurve(double x, double a, double b)
{
    double k = pow(a+b,a+b)/(pow(a,a)*pow(b,b));
    return k*pow(x,a)*pow(1.0-x,b);
}

double parabola(double x, double k)
{
    return pow( 4.0*x*(1.0-x), k);
}

double gain(double x, double k) 
{
    double a = 0.5*pow(2.0*((x<0.5)?x:1.0-x), k);
    return (x<0.5)?a:1.0-a;
}

double expStep(double x, double k, double n)
{
    return exp(-k*pow(x,n) );
}

double cubicPulse(double k, double w, double x)
{
    x = fabs(x - k);
    if( x>w ) return 0.;
    x /= w;
    return 1.0 - x*x*(3.0-2.0*x);
}

double expSustainedImpulse(double x, double f, double k)
{
    double s = max(x - f, 0.);
    return min(x * x/(f * f), 1. + (2.0/f) * s * exp(-k*s));
}

double polyImpulse(double k, double n, double x)					// -> n, le degrée de la fonction
{
    return (n/(n-1.0))*pow((n-1.0)*k,1.0/n)*x/(1.0+k*pow(x,n));
}

double expImpulse(double x, double k)
{
    double h = k*x;
    return h*exp(1.0-h);
}

double integralSmoothstep(double x, double T)
{
    if( x>T ) return x - T/2.0;
    return x*x*x*(1.0-x*0.5/T)/T/T;
}

double almostUnitIdentity(double x)
{
    return x*x*(2.0-x);
}


// Noises Functions