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
	/*Il nous faut réaliser un dégradé de couleurs...On a défini 5 couleurs
	* utilisées en fonction du nombre d'itérations. Chaque couleur doit tendre
	* vers celle qui la suit et celle qui la précède*/
	Color fractal;  //On crée une couleur pour le point en cours
	Color CouleurDAvant;   //On définit une couleur qui précède
	Color CouleurDApres;   //On définit une couleur qui suit
						   /*On définit un pas...4 couleurs, soit une toutes les (maxIterations / 4)*/
	double step = (double)myMaxIt / 4;
	/*On définit 3 coefficients, un par couleur*/
	double coeffR = 0;
	double coeffG = 0;
	double coeffB = 0;
	double red = 0., green = 0., blue = 0.;  //On définit 3 composantes R,G,B
	int variable = 0;
	int range = 10;

	if (iterations == myMaxIt)
		return myFractalColor;

	/* Pour les "pas" premières itérations, on cherche à passer de la couleur[0] à couleur[1]*/
	if (iterations <= step)
	{
		range = (int)step;
		variable = iterations;
		CouleurDAvant = myIterationsColors[0];   //Donc on les définit telles quelles
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

	/*On initialise nos coefficients, en faisant la différence des 2 composantes des 2 couleurs,
	* normalisés par un rapport pas.*/
	coeffR = (CouleurDApres.r - CouleurDAvant.r) / (double)range;
	coeffG = (CouleurDApres.g - CouleurDAvant.g) / (double)range;
	coeffB = (CouleurDApres.b - CouleurDAvant.b) / (double)range;

	//variable = (iterations%(int)pas); if (variable==0) variable = (int)pas;
	/*On crée les composantes rgb du point, en prenant la composante d'avant, à
	* laquelle on ajoute le coefficient multiplié par le pas (en gros)*/
	red = (CouleurDAvant.r + ((variable)) * coeffR);
	green = (CouleurDAvant.g + ((variable)) * coeffG);
	blue = (CouleurDAvant.b + ((variable)) * coeffB);

	if (myIsLogLog)  //Si adoucissement log-log choisi, calculs supplémentaires
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

	fractal = Color(red + coeffR, green + coeffG, blue + coeffB);   //On crée la couleur

	return fractal;
}