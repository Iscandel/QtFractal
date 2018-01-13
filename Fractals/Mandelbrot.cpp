#include "Mandelbrot.h"

#include "ObjectFactoryManager.h"

Mandelbrot::Mandelbrot()
:myIsLogLog(true)
,myMaxIt(100)
,myRefreshFrequency(10)
{
}


Mandelbrot::~Mandelbrot()
{
}

void Mandelbrot::computeFull(const Parameters& params)//, Array2D<Color>& out)
{
	Array2D<Color>& out = *myArray;

	const double XMIN = params.getDouble("xmin", -2.);
	const double XMAX = params.getDouble("xmax", 2.);
	const double YMIN = params.getDouble("ymin", -2.);
	const double YMAX = params.getDouble("ymax", 2.);
	myIsLogLog = params.getBool("loglog", false);
	myMaxIt = params.getInt("maxIter", 100);
	int width = out.getWidth();
	int height = out.getHeight();
	
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

	int cpt = 0;  //Un compteur, pour la barre de progression
	int coeffRefresh = 0;

	for (int i = 0; i < width; i++)		//boucle sur tous les pixels de l’image
	{
		for (int j = 0; j < height; j++)
		{
			//if (Stop.getStop())    //Si on a cliqué sur Stop
			//{
			//	i = largeur - 1;  //On passe aux derniers pixels de l'image, pour arrêter. On pourrait aussi faire un break
			//	j = hauteur - 1;
			//	/*On prévient l'utilisateur*/
			//	JOptionPane.showMessageDialog(null,
			//		"Interruption du calcul.", "Information",
			//		JOptionPane.INFORMATION_MESSAGE);
			//}

			/*On calcule le point courant. Il est situé entre XMIN et XMAX (resp. YMIN et YMAX),
			*  et il y a largeur points entre XMIN et XMAX (resp. longueur points entre YMIN etYMAX)*/
			double a = XMIN + i * (XMAX - XMIN) / width;
			double b = YMIN + j * (YMAX - YMIN) / height;
			double preciseIter;
			int iterations;
			if (!escapesToInfinity(a, b, iterations, preciseIter))
			{
				//argb = fractalColor.getRGB();   //Affecte le code RGB à un entier (compris entre 0 et 256^3)

				out(i, j) = Color(1., 0., 0.);
			}

			else  //Si ça ne diverge pas
			{
				//if (typeRepresentation == "Dégradé de gris") //On regarde le mode de représentation graphique choisi -Gris ici-
				{
					double coeff = 255 / myMaxIt;    //On calcule le coefficient, pour la couleur
					int rgb;

					if (!myIsLogLog)
						rgb = (int)(iterations*coeff);
					else  //Adoucissement log-log
					{
						double fin = preciseIter - iterations;
						double coeff2 = fin *coeff;
						rgb = (int)((iterations*coeff) + coeff2);
						rgb = rgb > 255 ? 255 : rgb;
					}

					/*On détermine la couleur pour le point en cours de calcul,
					dépendante du nombre d'itérations*/
					Color fractal = Color(rgb / 255.);

					out(i, j) = fractal;

					//argb = fractal.getRGB();    //On récupère le code RGB de la couleur
					//colorData = model.getDataElements(argb, null);
					//raster.setDataElements(i, j, colorData);
				}
			}
			int perc = (int)(((double)cpt / (width * height)) * 100);
			if (perc > myRefreshFrequency * coeffRefresh)
			{
				dispatchComputationAdvances(perc);
				coeffRefresh++;
			}
			cpt++;
		}
	}
}

Color Mandelbrot::computePixel(double a, double b, const Parameters& params)//, Array2D<Color>& out)
{
	//Array2D<Color>& out = *myArray;

	//const double XMIN = params.getDouble("xmin", -2.);
	//const double XMAX = params.getDouble("xmax", 2.);
	//const double YMIN = params.getDouble("ymin", -2.);
	//const double YMAX = params.getDouble("ymax", 2.);
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

	//On calcule le point courant. Il est situé entre XMIN et XMAX (resp. YMIN et YMAX),
	//et il y a largeur points entre XMIN et XMAX (resp. longueur points entre YMIN etYMAX)
	//double a = XMIN + x * (XMAX - XMIN) / width;
	//double b = YMIN + y * (YMAX - YMIN) / height;
	double preciseIter;
	int iterations;
	if (!escapesToInfinity(a, b, iterations, preciseIter))
	{
		return Color(1., 0., 0.);
	}
	else  //Si ça ne diverge pas
	{
		//if (typeRepresentation == "Dégradé de gris") //On regarde le mode de représentation graphique choisi -Gris ici-
		{
			double coeff = 255 / myMaxIt;    //On calcule le coefficient, pour la couleur
			int rgb;

			if (!myIsLogLog)
				rgb = (int)(iterations*coeff);
			else  //Adoucissement log-log
			{
				double fin = preciseIter - iterations;
				double coeff2 = fin *coeff;
				rgb = (int)((iterations*coeff) + coeff2);
				rgb = rgb > 255 ? 255 : rgb;
			}

			/*On détermine la couleur pour le point en cours de calcul,
			dépendante du nombre d'itérations*/
			return Color(rgb / 255.);
		}
	}
}

bool Mandelbrot::escapesToInfinity(double a, double b, int& iterations, double& preciseIter)
{
	double x = 0.0;
	double y = 0.0;
	double xPrime = 0;
	double yPrime = 0;
	//   int iterations = 0;
	iterations = 0;  //On fixe le nombre d'itérations à 0
	do
	{
		double xnew = x * x - y * y + a;
		double ynew = 2 * x * y + b;

		double _xPrime = 2.*(x*xPrime - y*yPrime) + 1.;
		double _yPrime = 2.*(x*yPrime + y*xPrime);

		x = xnew;
		y = ynew;
		xPrime = _xPrime;
		yPrime = _yPrime;
		iterations++;
		if (iterations == myMaxIt) return false;
	} while (x*x + y*y <= 4);//x <= 2 && y <= 2);

	if (myIsLogLog)
		preciseIter = iterations + 1 - std::log(std::log(std::sqrt(x*x + y*y))) / std::log(2);
	else
	{
		for (int k = 0; k < 3; k++)
		{
			// P(z)^2 + Z
			double xnew = x*x - y*y + a;
			double ynew = 2.*x*y + b;
			// 2.P'(Z).P(Z) + 1
			double _xPrime = 2.*(x*xPrime - y*yPrime) + 1.;
			double _yPrime = 2.*(x*yPrime + y*xPrime);

			x = xnew;
			y = ynew;
			xPrime = _xPrime;
			yPrime = _yPrime;
		}
		double reDiv = x*xPrime + y*yPrime;
		double imDiv = x*yPrime - y*xPrime;

		//mode3D = (double)Math.atan2(imDiv, reDiv);

		preciseIter = -(float)(std::log(0.5* std::log(x*x + y*y) / std::log(2)) / std::log(2) - iterations - 3);
	}
	return true;
}

FACTORY_REGISTER_TYPE(Mandelbrot, Fractal)