#ifndef _MATHFUNC_H_
#define _MATHFUNC_H_


float clamp(float x, float min, float max);
float step(float a, float x);
float smoothStep(float edge0, float edge1, float x);
float invSmoothstep(float x);
float lerp(float v0, float v1, float t);  //  == mix() en glsl
float min(float a, float b);
float max(float a, float b);
float length(float x);
float normalize(float channel_input);
int truncate(int value);

#endif