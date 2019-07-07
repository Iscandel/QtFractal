#include "MandelJuliaPredefRandomRenderer.h"



MandelJuliaPredefRandomRenderer::MandelJuliaPredefRandomRenderer(const Parameters& params)
{
	myIsLogLog = params.getBool("logLog", false);
	myMaxIt = params.getInt("maxIter", 100);

	myFractalColor = params.getColor("fractalColor", Color());
	std::vector<boost::any> tmp = params.getVector("iterationColors", std::vector<boost::any>());
	for (auto elem : tmp) {
		myIterationsColors.push_back(boost::any_cast<Color>(elem));
	}
}


MandelJuliaPredefRandomRenderer::~MandelJuliaPredefRandomRenderer()
{
}

Color MandelJuliaPredefRandomRenderer::computeColor(int iterations, double preciseIter, double x, double y, double xPrime, double yPrime)
{
	/*Il nous faut r�aliser un d�grad� de couleurs...On a d�fini 5 couleurs
	* utilis�es en fonction du nombre d'it�rations. Chaque couleur doit tendre
	* vers celle qui la suit et celle qui la pr�c�de*/
	Color fractal;  //On cr�e une couleur pour le point en cours
	Color CouleurDAvant;   //On d�finit une couleur qui pr�c�de
	Color CouleurDApres;   //On d�finit une couleur qui suit
						   /*On d�finit un pas...4 couleurs, soit une toutes les (maxIterations / 4)*/
	double step = (double)myMaxIt / 4;
	/*On d�finit 3 coefficients, un par couleur*/
	double coeffR = 0;
	double coeffG = 0;
	double coeffB = 0;
	double red = 0., green = 0., blue = 0.;  //On d�finit 3 composantes R,G,B
	int variable = 0;
	int range = 10;

	if (iterations == myMaxIt)
		return myFractalColor;

	/* Pour les "pas" premi�res it�rations, on cherche � passer de la couleur[0] � couleur[1]*/
	if (iterations <= step)
	{
		range = (int)step;
		variable = iterations;
		CouleurDAvant = myIterationsColors[0];   //Donc on les d�finit telles quelles
		CouleurDApres = myIterationsColors[1];
	}
	else if (iterations > step && iterations <= 2 * step)   //Idem, couleur 1 -> 2
	{
		range = (int)(2 * step - step);
		variable = (int)(iterations - (step + 1));
		CouleurDAvant = myIterationsColors[1];
		CouleurDApres = myIterationsColors[2];
	}
	else if (iterations > 2 * step && iterations <= 3 * step)  //Idem, couleur 2 -> 3
	{
		range = (int)(3 * step - 2 * step);
		variable = (int)(iterations - (2 * step + 1));
		CouleurDAvant = myIterationsColors[2];
		CouleurDApres = myIterationsColors[3];
	}
	else if (iterations > 3 * step && iterations <= myMaxIt)  //Idem, couleur 3 -> 4
	{
		range = (int)(myMaxIt - 1 - 3 * step);
		variable = (int)(iterations - (3 * step + 1));
		CouleurDAvant = myIterationsColors[3];
		CouleurDApres = myIterationsColors[4];
	}

	/*On initialise nos coefficients, en faisant la diff�rence des 2 composantes des 2 couleurs,
	* normalis�s par un rapport pas.*/
	coeffR = (CouleurDApres.r - CouleurDAvant.r) / (double)range;
	coeffG = (CouleurDApres.g - CouleurDAvant.g) / (double)range;
	coeffB = (CouleurDApres.b - CouleurDAvant.b) / (double)range;

	//variable = (iterations%(int)pas); if (variable==0) variable = (int)pas;
	/*On cr�e les composantes rgb du point, en prenant la composante d'avant, �
	* laquelle on ajoute le coefficient multipli� par le pas (en gros)*/
	red = (CouleurDAvant.r + ((variable)) * coeffR);
	green = (CouleurDAvant.g + ((variable)) * coeffG);
	blue = (CouleurDAvant.b + ((variable)) * coeffB);

	if (myIsLogLog)  //Si adoucissement log-log choisi, calculs suppl�mentaires
	{
		double fin = preciseIter - iterations;

		coeffR = coeffR * fin;
		coeffG = coeffG * fin;
		coeffB = coeffB * fin;
		//red = (int)(red + coeffR) > 255 ? 255 : (int)(red + coeffR) < 0 ? 0 : (int)(red + coeffR);
		////System.out.println(rouge);
		//green = (int)(green + coeffG)> 255 ? 255 : (int)(green + coeffG)< 0 ? 0 : (int)(green + coeffG);
		//blue = (int)(blue + coeffB)> 255 ? 255 : (int)(blue + coeffB)< 0 ? 0 : (int)(blue + coeffB);
	}

	fractal = Color(red + coeffR, green + coeffG, blue + coeffB);   //On cr�e la couleur

	return fractal;
}