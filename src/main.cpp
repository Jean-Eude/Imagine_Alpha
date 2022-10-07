#include "../Include/Headers.h"
#include "../Include/Image.h"


int main(int argc, char **argv)
{
	Image ImgGray_avg("Ressources/Img.jpg");   // Définir une image pour chaque effet / filtre car sinon -> erreur mémoire (application des effets par dessus le 1er effet)
	Image ImgLum_lum("Ressources/Img.jpg");
	Image ImgInv_inv("Ressources/Img.jpg");
	Image ImgBgr_bgr("Ressources/Img.jpg");
	Image ImgTrh_trh("Ressources/Img.jpg");
	Image ImgBrg_brg("Ressources/Img.jpg");
	Image ImgCnt_cnt("Ressources/Img.jpg");
	Image ImgCnB_cnb("Ressources/Img.jpg");
	Image ImgSat_sat("Ressources/Img.jpg");
	Image ImgSol_sol("Ressources/Img.jpg");
	Image ImgGma_gma("Ressources/Img.jpg");


	Image ImgFlipX("Ressources/Img.jpg");
	Image ImgFlipY("Ressources/Img.jpg");


	Image ImgCon("Ressources/Img.jpg");

	//------------------------//
	//------- Effets --------//
	//----------------------//


	ImgGray_avg.grayscale_avg();
	ImgGray_avg.write("Ressources/gray_avg.jpg");

	ImgLum_lum.grayscale_lum();
	ImgLum_lum.write("Ressources/gray_lum.jpg");

	ImgInv_inv.inverse();
	ImgInv_inv.write("Ressources/inverse.jpg");

	ImgBgr_bgr.bgr();
	ImgBgr_bgr.write("Ressources/bgr.jpg");

	ImgTrh_trh.treshold(128);
	ImgTrh_trh.write("Ressources/treshold.jpg");

	ImgBrg_brg.brightness(-100);
	ImgBrg_brg.write("Ressources/brightness.jpg");

	ImgCnt_cnt.contrast(100);
	ImgCnt_cnt.write("Ressources/contrast.jpg");

	ImgCnB_cnb.ContrastAndBrightness(128, -100);
	ImgCnB_cnb.write("Ressources/contrast&brightness.jpg");

	ImgSat_sat.saturation(0.5);  // Intervalle [0,1]  0 --> gris , 1 --> couleur
	ImgSat_sat.write("Ressources/saturation.jpg");

	ImgSol_sol.solarize(52, 52, 52, false);  
	ImgSol_sol.write("Ressources/solarize.jpg");

	ImgGma_gma.gamma(2.0);  
	ImgGma_gma.write("Ressources/gamma.jpg");

	//------------------------------------------//
	//------- Modifications de l'image --------//
	//----------------------------------------//

	ImgFlipX.flipX();
	ImgFlipX.write("Ressources/FlipX.jpg");

	ImgFlipY.flipY();
	ImgFlipY.write("Ressources/FlipY.jpg");

	//------------------------------//
	//------- Convolutions --------//
	//----------------------------//



	return 0;
}