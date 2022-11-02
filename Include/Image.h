#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Headers.h"

enum ImageType
{
	PNG, JPG, BMP, TGA
};


class Image
{
public:

	Image(const char* filename, int channel_force = 0);
	Image(int w, int h, int channels = 3);
	Image(const Image& img);
	~Image();

	bool read(const char* filename, int channel_force = 0);
	bool write(const char* filename);

	ImageType get_file_type(const char* filename);	

	uint8_t* data = NULL;
	size_t size = 0;
	int w;
	int h;
	int channels;


	//------------------------//
	//------- Effets --------//
	//----------------------//
	
	Image& grayscale_avg();
	Image& grayscale_lum();
	Image& inverse();	
	Image& bgr();	
	Image& treshold(int treshold);
	Image& brightness(int brightness);
	Image& contrast(int contrast);
	Image& ContrastAndBrightness(int contrast, int brightness);
	Image& saturation(double alpha);
	Image& solarize(int trsR, int trsG, int trsB, bool sabbatier);
	Image& gamma(double gamma);
	Image& huePerso(double levels);

	//---------------------------------//
	//------- Effets Spéciaux --------//
	//-------------------------------//

	Image& sepia();

	//------------------------------------------//
	//------- Modifications de l'image --------//
	//----------------------------------------//

	Image& flipX();
	Image& flipY();
	Image& CutIn2();
	Image& rescaleXY(int newHeight, int newWidth);

	//------------------------------//
	//------- Convolutions --------//
	//----------------------------//

	Image& std_convolve_clamp_to_0(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);
	Image& std_convolve_clamp_to_border(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);
	Image& std_convolve_cyclic(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);

	//------------------------------------------//
	//------- Others (Creating Images) --------//
	//----------------------------------------//

	Image& UniformColorBW(int BW);
	Image& UniformColorRGB(int r, int g, int b);
	Image& UniformGreyGradient();
	Image& UniformRGBGradient(int r, int g, int b);
	Image& LinearGradient(Vector3 col1, Vector3 col2);
	Image& ThreeColorsGradient(Vector3 col1, Vector3 col2, Vector3 col3, double length);
	Image& UVGradient();

	//-----------------------------------------------//
	//------- Others (Differents fonctions) --------//
	//-- https://thebookofshaders.com/05/?lan=fr --//
	//--------------------------------------------//

	Image& StepExample(double k);
	Image& SmoothstepExample(double k1, double k2);
	Image& SinExample();
	Image& CosExample();
	Image& ModExample(double k);
	Image& FracExample();
	Image& CeilExample();
	Image& FloorExample();
	Image& SignExample();
	Image& AbsExample();



	Image& SincExample(double k);
	Image& PowerCurveExample(double a, double b);
	Image& ParabolaExample(double k);
	Image& GainExample(double k);
	Image& ExpStepExample(double k, double n);
	Image& CubicPulseExample(double k, double w);
	Image& ExpSustainedImpulseExample(double f, double k);
	Image& PolyImpulseExample(double k, double n);
	Image& ExpImpulseExample(double k);
	Image& SmoothstepIntegralExample(double T);
	Image& UnitIdentityExample();
	
	// Advanced Functions --> https://iquilezles.org/articles/functions/


};

#endif