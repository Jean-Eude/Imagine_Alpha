#include "../Include/Headers.h"
#include "../Include/Image.h"


int main(int argc, char **argv)
{
	Image ImgGray_avg("Ressources/Img.jpg");   // Définir une image pour chaque effet / filtre car sinon -> erreur mémoire (application des effets par dessus le 1er effet)
	Image ImgLum_lum("Ressources/Img.jpg");
	Image ImgInv_inv("Ressources/Img.jpg");
	Image ImgTrh_trh("Ressources/Img.jpg");


	ImgGray_avg.grayscale_avg();
	ImgGray_avg.write("Ressources/gray_avg.png");

	ImgLum_lum.grayscale_lum();
	ImgLum_lum.write("Ressources/gray_lum.png");

	ImgInv_inv.inverse();
	ImgInv_inv.write("Ressources/inverse.png");

	ImgTrh_trh.treshold();
	ImgTrh_trh.write("Ressources/treshold.png");

	return 0;
}