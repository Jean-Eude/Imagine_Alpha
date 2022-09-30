#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION


#include "../Include/Headers.h"
#include "../Include/Stb.h"
#include "../Include/Image.h"
#include "../Include/MathFunc.h"


Image::Image(const char* filename, int channel_force) {
	if(read(filename, channel_force)) {
		printf("Read %s\n", filename);
		size = w*h*channels;
	}
	else {
		printf("Failed to read %s\n", filename);
	}
}

Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) {
	size = w*h*channels;
	data = new uint8_t[size];
}

Image::Image(const Image& img) : Image(img.w, img.h, img.channels) {
	memcpy(data, img.data, size);
}

Image::~Image() {
	stbi_image_free(data);
}

bool Image::read(const char* filename, int channel_force) {
	data = stbi_load(filename, &w, &h, &channels, channel_force);
	channels = channel_force == 0 ? channels : channel_force;
	return data != NULL;
}

bool Image::write(const char* filename) {
	ImageType type = get_file_type(filename);
	int success;
  switch (type) {
    case PNG:
      success = stbi_write_png(filename, w, h, channels, data, w*channels);
      break;
    case BMP:
      success = stbi_write_bmp(filename, w, h, channels, data);
      break;
    case JPG:
      success = stbi_write_jpg(filename, w, h, channels, data, 100);
      break;
    case TGA:
      success = stbi_write_tga(filename, w, h, channels, data);
      break;
  }
  if(success != 0) {
    printf("\e[32mWrote \e[36m%s\e[0m, %d, %d, %d, %zu\n", filename, w, h, channels, size);
    return true;
  }
  else {
    printf("\e[31;1m Failed to write \e[36m%s\e[0m, %d, %d, %d, %zu\n", filename, w, h, channels, size);
    return false;
  }
}

ImageType Image::get_file_type(const char* filename) {
	const char* ext = strrchr(filename, '.');
	if(ext != nullptr) {
		if(strcmp(ext, ".png") == 0) {
			return PNG;
		}
		else if(strcmp(ext, ".jpg") == 0) {
			return JPG;
		}
		else if(strcmp(ext, ".bmp") == 0) {
			return BMP;
		}
		else if(strcmp(ext, ".tga") == 0) {
			return TGA;
		}
	}
	return PNG;
}


//------------------------//
//------- Effets --------//
//----------------------//


Image& Image::grayscale_avg()
{
	float gray = 0;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i< size; i+=channels)
		{
			gray = (data[i] + data[i+1] + data[i+2]) / 3;
			memset(data+i, (int)gray, 3); // Fonction qui permet d'attribuer pour chaque channels la valeur gray
		}
	}
	return *this;
}


Image& Image::grayscale_lum()
{
	float gray = 0;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i< size; i+=channels)
		{
			gray = data[i] * 0.2627 + data[i+1] * 0.6780 + data[i+2] * 0.0593;
			memset(data+i, (int)gray, 3); // Fonction qui permet d'attribuer pour chaque channels la valeur gray
		}
	}
	return *this;
}


Image& Image::inverse()
{
	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i< size; i+= channels)
		{
			data[i] = 255 - data[i];
			data[i+1] = 255 - data[i+1];
			data[i+2] = 255 - data[i+2];
		}
	}
	return *this;
}


Image& Image::treshold()
{
	float gray;
	float b;
	float t;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i< size; i+= channels)
		{
			gray = (data[i] + data[i+1] + data[i+2]) / 3;
			b = lerp(0.0, 255.0, step(100, gray));
			t = (data[i] + data[i+1] + data[i+2]) * b;

			memset(data+i, (int)t, 3);
		}
	}
	return *this;
}