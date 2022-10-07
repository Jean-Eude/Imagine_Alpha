#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION


#include "../Include/Headers.h"
#include "../Include/Stb.h"
#include "../Include/Image.h"
#include "../Include/MathFunc.h"

using namespace std;

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


Image& Image::grayscale_avg() // ----> Intervalle [0,255]
{
	double gray = 0;

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
	return *this;		// OK
}


Image& Image::grayscale_lum() // ----> Intervalle [0,255]
{
	double gray = 0;

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
	return *this;		// OK
}


Image& Image::inverse() // ----> Intervalle [0,255]
{
	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i< size; i+= channels)
		{
			data[i] = (int) 255.0 - data[i];			
			data[i+1] = (int) 255.0 - data[i+1];
			data[i+2] = (int) 255.0 - data[i+2];
		}
	}
	return *this;		// OK
}



// Fonction qui inverse les channels RGB en BGR.

Image& Image::bgr() // ----> Intervalle [0,255]
{
	int r;
	int g;
	int b;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i< size; i+= channels)
		{
			r = data[i];
			g = data[i+1];
			b = data[i+2];

			data[i] = (int) b;
			data[i+1] = (int) g;
			data[i+2] = (int) r;
		}
	}
	return *this;		// OK
}


Image& Image::treshold(int treshold) // ----> Intervalle [0,255]
{
	double gray;
	double b;
	double t;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i< size; i+= channels)
		{
			gray = data[i] * 0.2627 + data[i+1] * 0.6780 + data[i+2] * 0.0593;	
			b = lerp(0.0, 255.0, step(treshold, gray));   											

			memset(data+i, (int)b, 3);
		}
	}
	return *this;		// OK
}



Image& Image::brightness(int brightness) // ----> Intervalle [0,255]
{
	double np1;
	double np2;
	double np3;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i< size; i+=channels)
		{
			np1 = data[i] + brightness;
			np2 = data[i+1] + brightness;
			np3 = data[i+2] + brightness;										

			np1 = clamp(np1, 0.0, 255.0);
			np2 = clamp(np2, 0.0, 255.0);
			np3 = clamp(np3, 0.0, 255.0);

			data[i] = (int) np1;
			data[i+1] = (int) np2;
			data[i+2] = (int) np3;
		}
	}
	return *this;		// OK	
}


Image& Image::contrast(int contrast) // ----> Intervalle [0,255]   
{
	double np1;
	double np2;
	double np3;

	double factor;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i< size; i+=channels)
		{
			factor = (259.0 * (contrast + 255.0)) / (255.0 * (259.0 - contrast));

			np1 = clamp((factor * (data[i] - 128.0) + 128.0), 0.0, 255.0);
			np2 = clamp((factor * (data[i+1] - 128.0) + 128.0), 0.0, 255.0);
			np3 = clamp((factor * (data[i+2] - 128.0) + 128.0), 0.0, 255.0);

			data[i] = (int) np1;
			data[i+1] = (int) np2;
			data[i+2] = (int) np3;
		}
	}
	return *this;		// OK
}


Image& Image::ContrastAndBrightness(int contrast, int brightness) // ----> Intervalle [0,128]  contrast = [0,125] / brightness = [-128,128]
{
	double np1;
	double np2;
	double np3;

	double factor;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i< size; i+=channels)
		{
			factor = (259.0 * (contrast + 255.0)) / (255.0 * (259.0 - contrast));

			np1 = clamp((factor * (data[i] - 128.0) + 128.0 + brightness), 0.0, 255.0);
			np2 = clamp((factor * (data[i+1] - 128.0) + 128.0 + brightness), 0.0, 255.0);
			np3 = clamp((factor * (data[i+2] - 128.0) + 128.0 + brightness), 0.0, 255.0);

			data[i] = (int) np1;
			data[i+1] = (int) np2;
			data[i+2] = (int) np3;
		}
	}
	return *this;		// OK
}


Image& Image::saturation(double alpha) // ----> Intervalle [0,1]
{
	double gray;

	double np1;
	double np2;
	double np3;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i< size; i+=channels)
		{
			gray = data[i] * 0.2627 + data[i+1] * 0.6780 + data[i+2] * 0.0593;

			np1 = gray;
			np2 = gray;
			np3 = gray;

			np1 = lerp(np1, data[i], alpha);
			np2 = lerp(np2, data[i+1], alpha);
			np3 = lerp(np3, data[i+2], alpha);

			data[i] = (int) np1;
			data[i+1] = (int) np2;
			data[i+2] = (int) np3;
		}
	}
	return *this;		// OK
}


Image& Image::solarize(int trsR, int trsG, int trsB, bool sabbatier) // ----> Intervalle [0,255]
{
	double gray;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i< size; i+=channels)
		{
			if(data[i] < trsR)
			{
				data[i] = (int) 255.0 - data[i];
			}
			if(data[i+1] < trsG)
			{
				data[i+1] = (int) 255.0 - data[i+1];
			}
			if(data[i+2] < trsB)
			{
				data[i+2] = (int) 255.0 - data[i+2];
			}

			if(sabbatier == true)
			{
				gray = data[i] * 0.2627 + data[i+1] * 0.6780 + data[i+2] * 0.0593; 
				memset(data+i, (int)gray, 3);
			}
		}
	}
	return *this;		// OK
}


Image& Image::gamma(double gamma) // ----> Intervalle [0,1]   !!: typage en doublage obligatoire ici !
{
	double gammaCorrection = 1 / gamma;

	double np1;
	double np2;
	double np3;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i< size; i+=channels)
		{
			np1 = 255.0 * pow(data[i] / 255.0, gammaCorrection);
			np2 = 255.0 * pow(data[i+1] / 255.0, gammaCorrection);
			np3 = 255.0 * pow(data[i+2] / 255.0, gammaCorrection);

			data[i] = (int) np1;
			data[i+1] = (int) np2;
			data[i+2] = (int) np3;
		}
	}
	return *this;		// OK
}




//posterize , equalize -> https://fr.wikipedia.org/wiki/%C3%89galisation_d%27histogramme,  ++++


//---------------------------------//
//------- Effets Spéciaux --------//
//-------------------------------//


// sepia vintage etc... --> https://pinetools.com/filters-image



//------------------------------------------//
//------- Modifications de l'image --------//
//----------------------------------------//

Image& Image::flipX()
{
	uint8_t tmp[4];
	uint8_t *px1;
	uint8_t *px2;
	
	for(int y = 0; y < h; ++y)
	{
		for(int x = 0; x < w/2; ++x)
		{
			px1 = &data[(x + y * w) * channels];
			px2 = &data[((w - 1 - x) + y * w) * channels];

			memcpy(tmp, px1, channels);
			memcpy(px1, px2, channels);
			memcpy(px2, tmp, channels);
		}
	}
	return *this;
}



Image& Image::flipY()
{
	uint8_t tmp[4];
	uint8_t *px1;
	uint8_t *px2;
	
	for(int x = 0; x < w; ++x)
	{
		for(int y = 0; y < h/2; ++y)
		{
			px1 = &data[(x + y * w) * channels];
			px2 = &data[(x + (h - 1 - y) * w) * channels];

			memcpy(tmp, px1, channels);
			memcpy(px1, px2, channels);
			memcpy(px2, tmp, channels);
		}
	}
	return *this;
}


//------------------------------//
//------- Convolutions --------//
//----------------------------//

