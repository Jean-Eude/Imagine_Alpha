#ifndef _MATHFUNC_H_
#define _MATHFUNC_H_

#include "Headers.h"

// Basic Functions

double clamp(double x, double min, double max);
double step(double a, double x);
double smoothstep(double edge0, double edge1, double x);
double invSmoothstep(double x);
double lerp(double v0, double v1, double t);  //  == mix() en glsl
double min(double a, double b);
double max(double a, double b);
double length(double x);
double normalize(double channel_input);
int truncate(int value);

double mod(double x, double a);
double fract (double x);
double sign (double x);

// Advanced Functions  --> https://iquilezles.org/articles/functions/

double sinc(double x, double k);
double pcurve(double x, double a, double b);
double parabola(double x, double k);
double gain(double x, double k);
double expStep(double x, double k, double n);
double cubicPulse(double k, double w, double x);
double expSustainedImpulse(double x, double f, double k);
double polyImpulse(double k, double n, double x);
double expImpulse(double x, double k);
double integralSmoothstep(double x, double T);
double almostUnitIdentity(double x);

// Random noises functions


#endif