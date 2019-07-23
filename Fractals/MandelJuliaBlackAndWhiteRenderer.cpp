#include "MandelJuliaBlackAndWhiteRenderer.h"



MandelJuliaBlackAndWhiteRenderer::MandelJuliaBlackAndWhiteRenderer(const Parameters& params)
{
	myIsLogLog = params.getBool("logLog", false);
	myMaxIt = params.getInt("maxIter", 100);
	myFractalColor = params.getColor("fractalColor", Color());
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
MandelJuliaBlackAndWhiteRenderer::~MandelJuliaBlackAndWhiteRenderer()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color MandelJuliaBlackAndWhiteRenderer::computeColor(int iterations, double preciseIter, double x, double y, double xPrime, double yPrime)
{
	double coeff = 255 / myMaxIt;    //On calcule le coefficient, pour la couleur
	int rgb;

	if (iterations == myMaxIt)
		return myFractalColor;

	if (!myIsLogLog)
		rgb = (int)(iterations*coeff);
	else  //Adoucissement log-log
	{
		double fin = preciseIter - iterations;
		double coeff2 = fin *coeff;
		rgb = (int)((iterations*coeff) + coeff2);
		rgb = rgb > 255 ? 255 : rgb;
	}

	/*On d�termine la couleur pour le point en cours de calcul,
	d�pendante du nombre d'it�rations*/
	return Color(rgb / 255.);
}