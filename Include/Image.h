#ifndef IMAGE_H
#define IMAGE_H

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


	Image& grayscale_avg();
	Image& grayscale_lum();
	Image& inverse();	
	Image& treshold();


	uint8_t* data = NULL;
	size_t size = 0;
	int w;
	int h;
	int channels;
};

#endif