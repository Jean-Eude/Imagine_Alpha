#include "../Include/Headers.h"
#include "../Include/Image.h"


int main(int argc, char **argv)
{
	//------------------------//
	//------- Effets --------//
	//----------------------//


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
	Image ImgHuePerso_hue("Ressources/Img.jpg");


	ImgGray_avg.grayscale_avg();
	ImgGray_avg.write("Ressources/Image_Processing/gray_avg.jpg");

	ImgLum_lum.grayscale_lum();
	ImgLum_lum.write("Ressources/Image_Processing/gray_lum.jpg");

	ImgInv_inv.inverse();
	ImgInv_inv.write("Ressources/Image_Processing/inverse.jpg");

	ImgBgr_bgr.bgr();
	ImgBgr_bgr.write("Ressources/Image_Processing/bgr.jpg");

	ImgTrh_trh.treshold(128);
	ImgTrh_trh.write("Ressources/Image_Processing/treshold.jpg");

	ImgBrg_brg.brightness(-100);
	ImgBrg_brg.write("Ressources/Image_Processing/brightness.jpg");

	ImgCnt_cnt.contrast(100);
	ImgCnt_cnt.write("Ressources/Image_Processing/contrast.jpg");

	ImgCnB_cnb.ContrastAndBrightness(128, -100);
	ImgCnB_cnb.write("Ressources/Image_Processing/contrast&brightness.jpg");

	ImgSat_sat.saturation(0.5);  // Intervalle [0,1]  0 --> gris , 1 --> couleur
	ImgSat_sat.write("Ressources/Image_Processing/saturation.jpg");

	ImgSol_sol.solarize(52, 52, 52, false);  
	ImgSol_sol.write("Ressources/Image_Processing/solarize.jpg");

	ImgGma_gma.gamma(2.0);  
	ImgGma_gma.write("Ressources/Image_Processing/gamma.jpg");

	ImgHuePerso_hue.huePerso(2);  
	ImgHuePerso_hue.write("Ressources/Image_Processing/huePerso.jpg");


	//---------------------------------//
	//------- Effets Spéciaux --------//
	//-------------------------------//


	Image ImgSep_sep("Ressources/Img.jpg");

	ImgSep_sep.sepia();  
	ImgSep_sep.write("Ressources/Image_Processing/sepia.jpg");


	//------------------------------------------//
	//------- Modifications de l'image --------//
	//----------------------------------------//

	
	Image ImgFlipX("Ressources/Img.jpg");
	Image ImgFlipY("Ressources/Img.jpg");
	Image ImgCutIn2("Ressources/Img.jpg");
	Image ImgRotate("Ressources/Img.jpg");
	Image ImgScale("Ressources/Image_Processing/treshold.jpg");


	ImgFlipX.flipX();
	ImgFlipX.write("Ressources/Image_Processing/FlipX.jpg");

	ImgFlipY.flipY();
	ImgFlipY.write("Ressources/Image_Processing/FlipY.jpg");

	ImgCutIn2.CutIn2();
	ImgCutIn2.write("Ressources/Image_Processing/CutIn2.jpg");

	ImgScale.rescaleXY(400, 400);
	ImgScale.write("Ressources/Image_Processing/Scale.jpg");
	


	//------------------------------//
	//------- Convolutions --------//
	//----------------------------//

	

	//------------------------------------------//
	//------- Others (Creating Images) --------//
	//----------------------------------------//

	Image Img_UCBW_ucbw(1920, 1080, 3);
	Image Img_UCRGB_ucrgb(1920, 1080, 3);
	Image Img_UGG_ugg(1920, 1080, 3);
	Image Img_URGBG_urgbg(1920, 1080, 3);
	Image Img_LING_ling(1920, 1080, 3);
	Image Img_3LN_3ln(1920, 1080, 3);
	Image Img_UVG_uvg(1920, 1080, 3);


	Img_UCBW_ucbw.UniformColorBW(128);
	Img_UCBW_ucbw.write("Ressources/Generative_Art/UniformColorBW.jpg");

	Img_UCRGB_ucrgb.UniformColorRGB(255, 255, 0);
	Img_UCRGB_ucrgb.write("Ressources/Generative_Art/UniformColorRGB.jpg");

	Img_UGG_ugg.UniformGreyGradient();
	Img_UGG_ugg.write("Ressources/Generative_Art/UniformGreyGradient.jpg");

	Img_URGBG_urgbg.UniformRGBGradient(145, 50, 255);
	Img_URGBG_urgbg.write("Ressources/Generative_Art/UniformRGBGradient.jpg");


	Vector3 color1(255, 0, 0);
	Vector3 color2(0, 0, 255);
	Img_LING_ling.LinearGradient(color1, color2);
	Img_LING_ling.write("Ressources/Generative_Art/LinearGradient.jpg");


	Vector3 color12(255, 0, 0);
	Vector3 color22(0, 255, 0);
	Vector3 color32(0, 0, 255);
	Img_3LN_3ln.ThreeColorsGradient(color12, color22, color32, 0.5);
	Img_3LN_3ln.write("Ressources/Generative_Art/3ColorsGradient.jpg");
	
	
	//-----------------------------------------------//
	//------- Others (Differents fonctions) --------//
	//-- https://thebookofshaders.com/05/?lan=fr --//
	//--------------------------------------------//

/*
	Image Img_STE_ste(1920, 1080, 3);
	Image Img_SSTE_sste(1920, 1080, 3);
	Image Img_SIN_sin(1920, 1080, 3);
	Image Img_COS_cos(1920, 1080, 3);
	Image Img_MOD_mod(1920, 1080, 3);
	Image Img_FRAC_frac(1920, 1080, 3);
	Image Img_CEIL_ceil(1920, 1080, 3);
	Image Img_FLOOR_floor(1920, 1080, 3);
	Image Img_SIGN_sign(1920, 1080, 3);
	Image Img_ABS_abs(1920, 1080, 3);



	Image Img_SINC_sinc(1920, 1080, 3);
	Image Img_PCURVE_pcurve(1920, 1080, 3);
	Image Img_PARAB_parab(1920, 1080, 3);
	Image Img_GAIN_gain(1920, 1080, 3);
	Image Img_EXPST_expst(1920, 1080, 3);
	Image Img_CUBIC_cubic(1920, 1080, 3);
	Image Img_EXPSTIMP_expstimp(1920, 1080, 3);
	Image Img_POLYIMP_polyimp(1920, 1080, 3);
	Image Img_EXPIMP_expimp(1920, 1080, 3);
	Image Img_SMTINT_smtint(1920, 1080, 3);
	Image Img_UID_uid(1920, 1080, 3);


	Img_STE_ste.StepExample(0.5);
	Img_STE_ste.write("Ressources/ShapingFunctions/StepExample.jpg");

	Img_SSTE_sste.SmoothstepExample(0.1, 0.9);
	Img_SSTE_sste.write("Ressources/ShapingFunctions/SmoothstepExample.jpg");

	Img_SIN_sin.SinExample();
	Img_SIN_sin.write("Ressources/ShapingFunctions/SinusExample.jpg");

	Img_COS_cos.CosExample();
	Img_COS_cos.write("Ressources/ShapingFunctions/CosinusExample.jpg");

	Img_MOD_mod.ModExample(0.9);
	Img_MOD_mod.write("Ressources/ShapingFunctions/ModuloExample.jpg");

	Img_FRAC_frac.FracExample();
	Img_FRAC_frac.write("Ressources/ShapingFunctions/FracExample.jpg");

	Img_CEIL_ceil.CeilExample();
	Img_CEIL_ceil.write("Ressources/ShapingFunctions/CeilExample.jpg");

	Img_FLOOR_floor.FloorExample();
	Img_FLOOR_floor.write("Ressources/ShapingFunctions/FloorExample.jpg");

	Img_SIGN_sign.SignExample();
	Img_SIGN_sign.write("Ressources/ShapingFunctions/SignExample.jpg");

	Img_ABS_abs.AbsExample();
	Img_ABS_abs.write("Ressources/ShapingFunctions/AbsExample.jpg");




	Img_SINC_sinc.SincExample(0.2);
	Img_SINC_sinc.write("Ressources/ShapingFunctions/SincExample.jpg");

	Img_PCURVE_pcurve.PowerCurveExample(3.0, 1.0);  
	Img_PCURVE_pcurve.write("Ressources/ShapingFunctions/PowerCurvesExample.jpg");

	Img_PARAB_parab.ParabolaExample(0.5);  
	Img_PARAB_parab.write("Ressources/ShapingFunctions/ParabolaExample.jpg");

	Img_GAIN_gain.GainExample(0.7);  
	Img_GAIN_gain.write("Ressources/ShapingFunctions/GainExample.jpg");

	Img_EXPST_expst.ExpStepExample(10., 1.0);  
	Img_EXPST_expst.write("Ressources/ShapingFunctions/ExponentialStepExample.jpg");

	Img_CUBIC_cubic.CubicPulseExample(0.5, 0.2);  
	Img_CUBIC_cubic.write("Ressources/ShapingFunctions/CubicPulseExample.jpg");

	Img_EXPSTIMP_expstimp.ExpSustainedImpulseExample(2.0, 0.2); 
	Img_EXPSTIMP_expstimp.write("Ressources/ShapingFunctions/ExpSustainedImpulseExample.jpg");

	Img_POLYIMP_polyimp.PolyImpulseExample(0.5, 2); 
	Img_POLYIMP_polyimp.write("Ressources/ShapingFunctions/PolyImpulseExample.jpg");

	Img_EXPIMP_expimp.ExpImpulseExample(0.3);
	Img_EXPIMP_expimp.write("Ressources/ShapingFunctions/ExpImpulseExample.jpg");

	Img_SMTINT_smtint.SmoothstepIntegralExample(0.3);
	Img_SMTINT_smtint.write("Ressources/ShapingFunctions/SmoothstepIntegralExample.jpg");

	Img_UID_uid.UnitIdentityExample();
	Img_UID_uid.write("Ressources/ShapingFunctions/UnitIdentityExample.jpg");

	*/

	return 0;
}