#include "Julia.h"

#include "renderer/MandelJuliaBlackAndWhiteRenderer.h"
#include "renderer/MandelJuliaPredefRandomRenderer.h"
#include "renderer/MandelJuliaSineRenderer.h"

#include "factory/ObjectFactoryManager.h"

Julia::Julia(const Parameters& params)
:myIsLogLog(false)
,myMaxIt(100)
,myRefreshFrequency(10)
,myInitialX(-0.181)
,myInitialY(0.667)
, myStrRenderer(params.getString("renderer", "Black & white"))
{
	initRenderer(myStrRenderer, params);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Julia::~Julia()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Julia::initRenderer(const std::string& renderer, const Parameters& params)
{
	if (renderer == "Black & white")
	{
		myRenderer = std::make_unique<MandelJuliaBlackAndWhiteRenderer>(params);
	}
	else if (renderer == "Random")
	{
		myRenderer = std::make_unique<MandelJuliaPredefRandomRenderer>(params);
	}
	else if (renderer == "Sine")
	{
		myRenderer = std::make_unique<MandelJuliaSineRenderer>(params);
	}
	else
	{
		ILogger::log() << "unknown renderer " << renderer << "\n";
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color Julia::computePixel(double a, double b, const Parameters& params, ParserById& parserById)//, Array2D<Color>& out)
{
	//Array2D<Color>& out = *myArray;

	myIsLogLog = params.getBool("loglog", false);
	myMaxIt = params.getInt("maxIter", 100);
	//int width = out.getWidth();
	//int height = out.getHeight();

	//for (int i = 0; i < 6;i++)          //On sauvegarde le tableau de couleurs de l'objet Infos
	//	Couleurs[i] = Infos.getCouleur(i);

	//BufferedImage image = new BufferedImage(largeur, hauteur, BufferedImage.TYPE_INT_ARGB);
	////création de l’image au moyen de la classe BufferedImage
	//WritableRaster raster = image.getRaster();
	////appel de la méthode getRaster() afin d’obtenir un objet de type WritableRaster, vous    
	////permettant d’accéder aux pixels de l’image et de les modifier.
	//ColorModel model = image.getColorModel(); //renvoie le modèle de couleur de l’image       
	//										  //mémorisée.

	//this.maxIterations = Infos.getIterations();    //Sauvegarde du nombre max d'itérations
	//fractalColor = Couleurs[5];                   //Couleur de l'Ensemble
	//int argb = fractalColor.getRGB();             //Renvoie le code RGB de la couleur
	//Object colorData = model.getDataElements(argb, null);
	//this.typeRepresentation = Infos.getTypeRepresentation();
	//System.out.println(Infos.getTypeRepresentation());

	double preciseIter;
	int iterations;
	double x, y;
	double xPrime, yPrime;

	escapesToInfinity(a, b, myInitialX, myInitialY, iterations, preciseIter, x, y, xPrime, yPrime);
	return myRenderer->computeColor(iterations, preciseIter, x, y, xPrime, yPrime);

	//if (!escapesToInfinity(a, b, myInitialX, myInitialY, iterations, preciseIter))
	//{
	//	return Color(1., 0., 0.);
	//}
	//else  //Si ça ne diverge pas
	//{
	//	//if (typeRepresentation == "Dégradé de gris") //On regarde le mode de représentation graphique choisi -Gris ici-
	//	{
	//		double coeff = 255 / myMaxIt;    //On calcule le coefficient, pour la couleur
	//		int rgb;

	//		if (!myIsLogLog)
	//			rgb = (int)(iterations*coeff);
	//		else  //Adoucissement log-log
	//		{
	//			double fin = preciseIter - iterations;
	//			double coeff2 = fin *coeff;
	//			rgb = (int)((iterations*coeff) + coeff2);
	//			rgb = rgb > 255 ? 255 : rgb;
	//		}

	//		/*On détermine la couleur pour le point en cours de calcul,
	//		dépendante du nombre d'itérations*/
	//		return Color(rgb / 255.);
	//	}
	//}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool Julia::escapesToInfinity(double a, double b, double initialX, double initialY, int& iterations, double& preciseIter, double& x, double& y, double& xPrime, double& yPrime)
{
	x = initialX;       // -0.6;
	y = initialY;       //-0.5
	xPrime = 0;
	yPrime = 0;
	iterations = 0;

	do
	{
		double xnew = a * a - b * b + x;
		double ynew = 2 * a * b + y;

		double _xPrime = 2.*(a*xPrime - b*yPrime) + 1.;
		double _yPrime = 2.*(a*yPrime + b*xPrime);

		a = xnew;
		b = ynew;

		xPrime = _xPrime;
		yPrime = _yPrime;
		iterations++;
		if (iterations == myMaxIt) return false;
	} while (a*a + b*b <= 4);//a <= 2 && b <= 2);
	if (myIsLogLog)
		preciseIter = iterations + 1 - std::log(std::log(std::sqrt(a*a + b*b))) / std::log(2);
	else
	{
		for (int k = 0;k<3;k++)
		{
			// P(z)^2 + Z
			double xnew = a*a - b*b + x;
			double ynew = 2.*a*b + y;
			// 2.P'(Z).P(Z) + 1
			double _xPrime = 2.*(a*xPrime - b*yPrime) + 1.;
			double _yPrime = 2.*(a*yPrime + b*xPrime);

			a = xnew;
			b = ynew;
			xPrime = _xPrime;
			yPrime = _yPrime;
		}
		double reDiv = a*xPrime + b*yPrime;
		double imDiv = a*yPrime - b*xPrime;

		//mode3D = (double)Math.atan2(imDiv, reDiv);

		preciseIter = -(float)(std::log(0.5*std::log(a*a + b*b) / std::log(2)) / std::log(2) - iterations - 3);
	}
	return true;
}

FACTORY_REGISTER_TYPE(Julia, Fractal)