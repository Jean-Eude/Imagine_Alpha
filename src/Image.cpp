#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define BYTE_BOUND(value) value < 0 ? 0 : (value > 255 ? 255 : value)


#include "../Include/Headers.h"
#include "../Include/Stb.h"
#include "../Include/Image.h"
#include "../Include/MathFunc.h"
#include "../Include/Vector3.h"
#include "../Include/Vector2.h"


Image::Image(const char* filename, int channel_force) {
	if(read(filename, channel_force)) {
		printf("Read %s\n", filename);
		this->size = this->w*this->h*this->channels;
	}
	else {
		printf("Failed to read %s\n", filename);
	}
}

Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) {
	this->size = this->w*this->h*this->channels;
	this->data = new uint8_t[size];
}

Image::Image(const Image& img) : Image(img.w, img.h, img.channels) {
	memcpy(this->data, img.data, this->size);
}

Image::~Image() {
	stbi_image_free(this->data);
}

bool Image::read(const char* filename, int channel_force) {
	this->data = stbi_load(filename, &w, &h, &channels, channel_force);
	this->channels = channel_force == 0 ? this->channels : channel_force;
	return this->data != NULL;
}

bool Image::write(const char* filename) {
	ImageType type = get_file_type(filename);

	int success;

  switch (type) {
    case PNG:
      success = stbi_write_png(filename, this->w, this->h, this->channels, this->data, this->w*this->channels);
      break;
    case BMP:
      success = stbi_write_bmp(filename, this->w, this->h, this->channels, this->data);
      break;
    case JPG:
      success = stbi_write_jpg(filename, this->w, this->h, this->channels, this->data, 100);
      break;
    case TGA:
      success = stbi_write_tga(filename, this->w, this->h, this->channels, this->data);
      break;
  }
  if(success != 0) {
    printf("\e[32mWrote \e[36m%s\e[0m, %d, %d, %d, %zu\n", filename, this->w, this->h, this->channels, this->size);
    return true;
  }
  else {
    printf("\e[31;1m Failed to write \e[36m%s\e[0m, %d, %d, %d, %zu\n", filename, this->w, this->h, this->channels, this->size);
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
			memset(data+i, (uint8_t)gray, 3); // Fonction qui permet d'attribuer pour chaque channels la valeur gray
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
			memset(data+i, (uint8_t)gray, 3); // Fonction qui permet d'attribuer pour chaque channels la valeur gray
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
			data[i] = (uint8_t) 255.0 - data[i];			
			data[i+1] = (uint8_t) 255.0 - data[i+1];
			data[i+2] = (uint8_t) 255.0 - data[i+2];
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

			data[i] = (uint8_t) b;
			data[i+1] = (uint8_t) g;
			data[i+2] = (uint8_t) r;
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

			memset(data+i, (uint8_t)b, 3);
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

			data[i] = (uint8_t) np1;
			data[i+1] = (uint8_t) np2;
			data[i+2] = (uint8_t) np3;
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

			data[i] = (uint8_t) np1;
			data[i+1] = (uint8_t) np2;
			data[i+2] = (uint8_t) np3;
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

			data[i] = (uint8_t) np1;
			data[i+1] = (uint8_t) np2;
			data[i+2] = (uint8_t) np3;
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

			data[i] = (uint8_t) np1;
			data[i+1] = (uint8_t) np2;
			data[i+2] = (uint8_t) np3;
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
				data[i] = (uint8_t) 255.0 - data[i];
			}
			if(data[i+1] < trsG)
			{
				data[i+1] = (uint8_t) 255.0 - data[i+1];
			}
			if(data[i+2] < trsB)
			{
				data[i+2] = (uint8_t) 255.0 - data[i+2];
			}

			if(sabbatier == true)
			{
				gray = data[i] * 0.2627 + data[i+1] * 0.6780 + data[i+2] * 0.0593; 
				memset(data+i, (uint8_t)gray, 3);
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

			data[i] = (uint8_t) np1;
			data[i+1] = (uint8_t) np2;
			data[i+2] = (uint8_t) np3;
		}
	}

	return *this;		// OK
}



Image& Image::huePerso(double levels) 
{
	double r;
	double g;
	double b;
	double mine, maxe;
	double hue, luminance, saturation;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i< size; i+=channels)
		{
			r = data[i];
			g = data[i+1];
			b = data[i+2];

			mine = min(r, min(g, b));
			maxe = max(r, max(g, b));

			luminance = (mine+maxe)/2;

			if(luminance > 127)
			{
				saturation = (maxe-mine) / (maxe+mine);
			}
			else
			{
				saturation = (maxe-mine) / (510-maxe-mine);
			}


			if(maxe == r)
			{
				hue = (g-b) / (maxe-mine);
			}
			else if(maxe == g)
			{
				hue = 510 + (b-r) / (maxe-mine);
			}
			else
			{
				hue = 1020 + (r-g) / (maxe-mine);
			}

			hue *= levels;


			data[i] = (uint8_t) hue;
			data[i+1] = (uint8_t) saturation;
			data[i+2] = (uint8_t) luminance;
		}
	}

	return *this;		// OK
}


//posterize , equalize -> https://fr.wikipedia.org/wiki/%C3%89galisation_d%27histogramme,  ++++


//---------------------------------//
//------- Effets Spéciaux --------//
//-------------------------------//

Image& Image::sepia()
{
	double tr;
	double tg;
	double tb;

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
			tr = (int) (data[i] * 0.393 + data[i+1] * 0.769 + data[i+2] * 0.189);
			tg = (int) (data[i] * 0.349 + data[i+1] * 0.686 + data[i+2] * 0.168);
			tb = (int) (data[i] * 0.272 + data[i+1] * 0.534 + data[i+2] * 0.131);

			if(tr > 255)
			{
				np1 = 255;
			}
			else
			{
				np1 = tr;
			}


			if(tg > 255)
			{
				np2 = 255;
			}
			else
			{
				np2 = tg;
			}


			if(tb > 255)
			{
				np3 = 255;
			}
			else
			{
				np3 = tb;
			}

			data[i] = (uint8_t) np1;
			data[i+1] = (uint8_t) np2;
			data[i+2] = (uint8_t) np3;
		}
	}

	return *this;		// OK
}


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


Image& Image::CutIn2()
{
	uint8_t tmp[4];
	uint8_t *px1;
	uint8_t *px2;
	
	int x,y = 0;

	for(x = 0; x < w/2; ++x)
	{
		for(y = 0; y < h/2; ++y)
		{
			px1 = &data[(x + y * w) * channels];            // <--- Position courante dans l'image  == pixel(x,y)  px1 = src
			px2 = &data[(x + (h - 1 - y) * w) * channels];	// <--- h - 1 = offset  px2 = dest

			memcpy(tmp, px1, channels);
			memcpy(px1, px2, channels);
			memcpy(px2, tmp, channels);
		}
	}

	return *this;
}


Image& Image::rescaleXY(int newHeight, int newWidth)
{	
	size = newHeight * newWidth * channels;
	uint8_t *newImg = new uint8_t[size];

	double scaleX = (double)newWidth / (w);
	double scaleY = (double)newHeight / (h);
	uint16_t sx, sy;

	for(uint16_t y = 0;y < newHeight;++y) 
	{
		sy = (uint16_t)(y / scaleY);
		for(uint16_t x = 0;x < newWidth;++x) 
		{
			sx = (uint16_t)(x / scaleX);
			memcpy(&newImg[(x + y * newWidth) * channels], &data[(sx + sy * w) * channels], channels);
		}
	}

	w = newWidth;
	h = newHeight;
	size = w*h*channels;

	delete[] data;
	data = newImg;
	newImg = nullptr;

	return *this;
}


//------------------------------//
//------- Convolutions --------//
//----------------------------//


Image& Image::std_convolve_clamp_to_0(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc) 
{
	uint8_t new_data[w*h];
	uint64_t center = cr*ker_w + cc;
	for(uint64_t k=channel; k<size; k+=channels) {
		double c = 0;
		for(long i = -((long)cr); i<(long)ker_h-cr; ++i) {
			long row = ((long)k/channels)/w-i;
			if(row < 0 || row > h-1) {
				continue;
			}
			for(long j = -((long)cc); j<(long)ker_w-cc; ++j) {
				long col = ((long)k/channels)%w-j;
				if(col < 0 || col > w-1) {
					continue;
				}
				c += ker[center+i*(long)ker_w+j]*data[(row*w+col)*channels+channel];
			}
		}
		new_data[k/channels] = (uint8_t)BYTE_BOUND(round(c));
	}
	for(uint64_t k=channel; k<size; k+=channels) {
		data[k] = new_data[k/channels];
	}

	return *this;
}


Image& Image::std_convolve_clamp_to_border(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc) 
{
	uint8_t new_data[w*h];
	uint64_t center = cr*ker_w + cc;
	for(uint64_t k=channel; k<size; k+=channels) {
		double c = 0;
		for(long i = -((long)cr); i<(long)ker_h-cr; ++i) {
			long row = ((long)k/channels)/w-i;
			if(row < 0) {
				row = 0;
			}
			else if(row > h-1) {
				row = h-1;
			}
			for(long j = -((long)cc); j<(long)ker_w-cc; ++j) {
				long col = ((long)k/channels)%w-j;
				if(col < 0) {
					col = 0;
				}
				else if(col > w-1) {
					col = w-1;
				}
				c += ker[center+i*(long)ker_w+j]*data[(row*w+col)*channels+channel];
			}
		}
		new_data[k/channels] = (uint8_t)BYTE_BOUND(round(c));
	}
	for(uint64_t k=channel; k<size; k+=channels) {
		data[k] = new_data[k/channels];
	}

	return *this;
}


Image& Image::std_convolve_cyclic(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc) 
{
	uint8_t new_data[w*h];
	uint64_t center = cr*ker_w + cc;
	for(uint64_t k=channel; k<size; k+=channels) {
		double c = 0;
		for(long i = -((long)cr); i<(long)ker_h-cr; ++i) {
			long row = ((long)k/channels)/w-i;
			if(row < 0) {
				row = row%h + h;
			}
			else if(row > h-1) {
				row %= h;
			}
			for(long j = -((long)cc); j<(long)ker_w-cc; ++j) {
				long col = ((long)k/channels)%w-j;
				if(col < 0) {
					col = col%w + w;
				}
				else if(col > w-1) {
					col %= w;
				}
				c += ker[center+i*(long)ker_w+j]*data[(row*w+col)*channels+channel];
			}
		}
		new_data[k/channels] = (uint8_t)BYTE_BOUND(round(c));
	}
	for(uint64_t k=channel; k<size; k+=channels) {
		data[k] = new_data[k/channels];
	}

	return *this;
}


//------------------------------------------//
//------- Others (Creating Images) --------//
//----------------------------------------//


Image& Image::UniformColorBW(int BW)   // Couleur entre le blanc et le noir
{
	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i < size; i++) 
		{
			data[i] = (uint8_t) BW;
		}
	}

	return *this;		// OK
}


Image& Image::UniformColorRGB(int r, int g, int b) // Couleur uniforme
{
	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i < size; i+=channels) 
		{
			data[i] = (uint8_t)  r;
			data[i+1] = (uint8_t)  g;
			data[i+2] = (uint8_t)  b;
		}
	}

	return *this;		// OK
}


Image& Image::UniformGreyGradient()   // Gradient entre le blanc et le noir
{
	double c;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(int i = 0; i < size; i++) 
		{
			c = (double) i / ((double) size);		// c == uv = fragCoord/iResolution.xy;

			data[i] = (uint8_t) (255 * c);
			data[i+1] = (uint8_t) (255 * c);
			data[i+2] = (uint8_t) (255 * c);
		}
	}

	return *this;		// OK
}



Image& Image::UniformRGBGradient(int r, int g, int b)  // Gradient entre une couleur défini et le noir
{
	int i;
	double c;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);

			data[i] = (uint8_t)  (r * c);
			data[i+1] = (uint8_t)  (g * c);
			data[i+2] = (uint8_t)  (b * c);
		}
	}

	return *this;		// OK
}


Image& Image::LinearGradient(Vector3 col1, Vector3 col2)  // Gradient entre une couleur défini et une autre
{
	int i;
	double c, l1, l2, l3;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);				// Explications:  c représente la position 
			l1 = lerp(col1.x, col2.x, c);						// On applique une interpolation linéaire pour canal R, G, B de chaque chaque couleur
			l2 = lerp(col1.y, col2.y, c);						// suivant c
			l3 = lerp(col1.z, col2.z, c);

			data[i] = (uint8_t)  (l1);							// ! Pas besoin de multipler par une valeur [0,255] car l'interpolation linéaire 
			data[i+1] = (uint8_t)  (l2);						// retourne déjà une valeur [0,255]
			data[i+2] = (uint8_t)  (l3);
		}
	}

	return *this;		// OK
}


Image& Image::ThreeColorsGradient(Vector3 col1, Vector3 col2, Vector3 col3, double length)  // Gradient entre une couleur défini, une autre et une autre
{
	int i;
	double c, l1, l2, l3;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);				// Explications: c représente la position 
			l1 = lerp(col1.x, col2.x, c);						// On applique une interpolation linéaire pour canal R, G, B de chaque chaque couleur
			l2 = lerp(col1.y, col2.y, c);						// suivant c
			l3 = lerp(col1.z, col2.z, c);

			data[i] = (uint8_t)  (l1);							// ! Pas besoin de multipler par une valeur [0,255] car l'interpolation linéaire 
			data[i+1] = (uint8_t)  (l2);						// retourne déjà une valeur [0,255]
			data[i+2] = (uint8_t)  (l3);
		}
	}

	return *this;		// OK
}


//-----------------------------------------------//
//------- Others (Differents fonctions) --------//
//-- https://thebookofshaders.com/05/?lan=fr --//
//--------------------------------------------//
//-------------	Generative Art --------------//


Image& Image::StepExample(double k) 
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = step(k, c);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::SmoothstepExample(double k1, double k2)  
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = smoothstep(k1, k2, c);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::SinExample()  
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = sin(c);

			// https://thebookofshaders.com/05/?lan=fr   pour plus d'infos sur le sinus / cosinus

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::CosExample()  
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = cos(c);

			// https://thebookofshaders.com/05/?lan=fr   pour plus d'infos sur le sinus / cosinus

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::ModExample(double k)  
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = mod(c, k);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::FracExample()  
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = fract(c);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::CeilExample()  
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = ceil(c);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::FloorExample()  
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = floor(c);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::SignExample()  
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = sign(c);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::AbsExample()  
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = fabs(c);												// -> fabs(x) pour double, abs(x) pour int

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}





// Advanced Functions


Image& Image::SincExample(double k) 
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = sinc(c, k);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::PowerCurveExample(double a, double b)  
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = pcurve(c, a, b);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::ParabolaExample(double k)  
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = parabola(c, k);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::GainExample(double k)  
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = gain(c, k);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::ExpStepExample(double k, double n)  
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = expStep(c, k, n);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::CubicPulseExample(double k, double w)  
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = cubicPulse(k, w, c);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::ExpSustainedImpulseExample(double f, double k)     // -> f >= 1  et  0>k>1 
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = expSustainedImpulse(c, f, k);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::PolyImpulseExample(double k, double n)  	// -> n >= 2
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = polyImpulse(k, n, c);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::ExpImpulseExample(double k) 
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = expImpulse(c, k);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::SmoothstepIntegralExample(double T)
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = integralSmoothstep(c, T);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}


Image& Image::UnitIdentityExample()
{
	int i;
	double c, st;

	if(channels < 3)
	{
		printf("Image %p has less than 3 channels !", this);
	}
	else
	{
		for(i=0; i<size; i+=channels) 
		{
			c = (double) i / ((double) size);
			st = almostUnitIdentity(c);

			data[i] = (uint8_t)  (st * 255);							
			data[i+1] = (uint8_t)  (st * 255);						
			data[i+2] = (uint8_t)  (st * 255);
		}
	}

	return *this;		// OK
}