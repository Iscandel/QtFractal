#pragma once
#include "Fractal.h"

#include "renderer/MandelJuliaBaseRenderer.h"

class Julia :
	public GenericParallelizableFractal
{
	REGISTER_FRACTAL_PRATICAL_NAME(Julia)
public:
	Julia(const Parameters&);
	~Julia();

protected:
	bool escapesToInfinity(double a, double b, double xDepart, double yDepart, int& iterations, double& preciseIter, double& x, double& y, double& xPrime, double& yPrime);

	Color computePixel(double x, double y, const Parameters& params, ParserById& parserById) override;

	void initRenderer(const std::string& renderer, const Parameters& params);

protected:
	bool myIsLogLog;
	int myMaxIt;
	int myRefreshFrequency;

	double myInitialX;
	double myInitialY;

	std::string myStrRenderer;
	std::unique_ptr<MandelJuliaBaseRenderer> myRenderer;
};

//class Julia extends Fractale
//{
//	private static double XMIN = -2;
//	private static double XMAX = 2;
//	private static double YMIN = -2;
//	private static double YMAX = 2;
//	private int maxIterations = 50;
//	private Color fractalColor;// = Color.red;
//	private int iterations;
//	private String typeRepresentation;
//	private int largeur, hauteur;
//	private Color Couleurs[] = new Color[6];
//	private double iterPrecise;
//	private double mode3D;
//	private boolean logLog;
//
//	public BufferedImage construireFractale(JProgressBar Progression,
//		InfosParametres Infos, Stop Stop)
//	{
//
//		XMIN = Infos.LeRepere.getXMin();
//		XMAX = Infos.LeRepere.getXMax();
//		YMIN = Infos.LeRepere.getYMin();
//		YMAX = Infos.LeRepere.getYMax();
//		this.largeur = Infos.getLargeur();
//		this.hauteur = Infos.getHauteur();
//		logLog = Infos.getLogLog();
//		for (int i = 0; i < 6;i++)
//			Couleurs[i] = Infos.getCouleur(i);
//
//		BufferedImage image = new BufferedImage(largeur, hauteur, BufferedImage.TYPE_INT_ARGB);
//		//création de l’image au moyen de la classe BufferedImage
//		WritableRaster raster = image.getRaster();
//		//appel de la méthode getRaster() afin d’obtenir un objet de type WritableRaster, vous    
//		//permettant d’accéder aux pixels de l’image et de les modifier.
//		ColorModel model = image.getColorModel(); //renvoie le modèle de couleur de l’image       
//												  //mémorisée.
//
//		this.maxIterations = Infos.getIterations();
//		fractalColor = Couleurs[5];
//		int argb = fractalColor.getRGB();
//		Object colorData = model.getDataElements(argb, null);
//		this.typeRepresentation = Infos.getTypeRepresentation();
//
//		int cpt = 0;
//		int pourcentage = 1;
//		Progression.setValue(0);
//
//		for (int i = 0; i <largeur; i++)		//boucle sur tous les pixels de l’image
//			for (int j = 0; j < hauteur; j++)
//			{
//				if (Stop.getStop())
//				{
//					i = largeur - 1;
//					j = hauteur - 1;
//					JOptionPane.showMessageDialog(null,
//						"Interruption du calcul.", "Information",
//						JOptionPane.INFORMATION_MESSAGE);
//				}
//
//				double a = XMIN + i * (XMAX - XMIN) / largeur;
//				double b = YMIN + j * (YMAX - YMIN) / hauteur;
//				if (!escapesToInfinity(a, b, Infos.getXDepart(), Infos.getYDepart()))//appel à la fonction escapesToInfinity
//				{
//					argb = fractalColor.getRGB();
//					colorData = model.getDataElements(argb, null);
//
//					//si cela diverge : on affecte au point de 
//					// coordonnées (i,j) la couleur choisie
//					raster.setDataElements(i, j, colorData);
//				}
//
//				else
//				{
//					if (typeRepresentation == "Dégradé de gris")
//					{
//						double coeff = 255 / maxIterations;
//						int rgb;
//
//						if (!logLog)
//							rgb = (int)(iterations*coeff);
//						else  //Adoucissement log-log
//						{
//							double fin = iterPrecise - iterations;
//							double coeff2 = fin *coeff;
//							rgb = (int)((iterations*coeff) + coeff2);
//							rgb = rgb > 255 ? 255 : rgb;
//							//System.out.println(fin+" "+coeff2);
//						}
//
//						Color fractal = new Color(rgb, rgb, rgb);
//						//	Color fractal = new Color((int)(iterations*coeff),(int)(iterations*coeff),(int)(iterations*coeff));
//						argb = fractal.getRGB();
//						colorData = model.getDataElements(argb, null);
//						raster.setDataElements(i, j, colorData);
//					}
//					else if (typeRepresentation == "Prédéfini" || typeRepresentation == "Aléatoire")
//					{
//						Color fractal = Color.red;
//						Color CouleurDAvant = Color.red;
//						Color CouleurDApres = Color.red;
//						double pas = (double)maxIterations / 4;
//						double coeffR = 0;
//						double coeffG = 0;
//						double coeffB = 0;
//						int rouge = 0, vert = 0, bleu = 0;
//						int variable = 0;
//						int intervalle = 10;
//
//						if (iterations <= pas)
//						{
//							intervalle = (int)pas;
//							variable = iterations;   //"reste" nombre d'itérations entre l'intervalle (numéro de celle ci)
//							CouleurDAvant = Couleurs[0];
//							CouleurDApres = Couleurs[1];
//						}
//						else if (iterations > pas && iterations <= 2 * pas)
//						{
//							intervalle = (int)(2 * pas - pas);
//							variable = (int)(iterations - (pas + 1));
//							CouleurDAvant = Couleurs[1];
//							CouleurDApres = Couleurs[2];
//						}
//						else if (iterations > 2 * pas && iterations <= 3 * pas)
//						{
//							intervalle = (int)(3 * pas - 2 * pas);
//							variable = (int)(iterations - (2 * pas + 1));
//							CouleurDAvant = Couleurs[2];
//							CouleurDApres = Couleurs[3];
//						}
//						else if (iterations > 3 * pas && iterations < maxIterations)
//						{
//							intervalle = (int)(maxIterations - 1 - 3 * pas);
//							variable = (int)(iterations - (3 * pas + 1));
//							CouleurDAvant = Couleurs[3];
//							CouleurDApres = Couleurs[4];
//						}
//
//						coeffR = (CouleurDApres.getRed() - CouleurDAvant.getRed()) / (double)intervalle;
//						coeffG = (CouleurDApres.getGreen() - CouleurDAvant.getGreen()) / (double)intervalle;
//						coeffB = (CouleurDApres.getBlue() - CouleurDAvant.getBlue()) / (double)intervalle;
//
//						//variable = (iterations%(int)(intervalle + 1));// if (variable==0) variable = (int)pas;
//						rouge = (int)(CouleurDAvant.getRed() + ((variable)) * coeffR);
//						vert = (int)(CouleurDAvant.getGreen() + ((variable)) * coeffG);
//						bleu = (int)(CouleurDAvant.getBlue() + ((variable)) * coeffB);
//
//						if (logLog)
//						{
//							double fin = iterPrecise - iterations;
//
//							coeffR = coeffR * fin;
//							coeffG = coeffG * fin;
//							coeffB = coeffB * fin;
//							rouge = (int)(rouge + coeffR)>255 ? 255 : (int)(rouge + coeffR) < 0 ? 0 : (int)(rouge + coeffR);
//							vert = (int)(vert + coeffG)> 255 ? 255 : (int)(vert + coeffG)< 0 ? 0 : (int)(vert + coeffG);
//							bleu = (int)(bleu + coeffB)> 255 ? 255 : (int)(bleu + coeffB)< 0 ? 0 : (int)(bleu + coeffB);
//						}
//
//						fractal = new Color(rouge, vert, bleu);
//
//						argb = fractal.getRGB();
//						colorData = model.getDataElements(argb, null);
//						raster.setDataElements(i, j, colorData);
//					}
//					else if (typeRepresentation == "Potentiel")
//					{
//						Color fractal = Color.red;
//						int rouge = 0, vert = 0, bleu = 0;
//
//						double r = (double)(Infos.InfSin.getAmplitudeR()*Math.sin(
//							Infos.InfSin.getPulsationR()*iterPrecise + Infos.InfSin.getPhaseR()));
//						double g = (double)(Infos.InfSin.getAmplitudeG()*Math.sin(
//							Infos.InfSin.getPulsationG()*iterPrecise + Infos.InfSin.getPhaseG()));
//						double bl = (double)(Infos.InfSin.getAmplitudeB()*Math.sin(
//							Infos.InfSin.getPulsationB()*iterPrecise + Infos.InfSin.getPhaseB()));
//						//System.out.println((int)(rouge*255.99));
//						rouge = (int)(r*255.99) > 255 ? 255 : (int)(r*255.99) < 0 ? 0 : (int)(r*255.99);
//						vert = (int)(g*255.99)> 255 ? 255 : (int)(g*255.99)< 0 ? 0 : (int)(g*255.99);
//						bleu = (int)(bl*255.99)> 255 ? 255 : (int)(bl*255.99)< 0 ? 0 : (int)(bl*255.99);
//
//						fractal = new Color(rouge, vert, bleu);   //On crée la couleur
//
//						argb = fractal.getRGB();
//						colorData = model.getDataElements(argb, null);
//						raster.setDataElements(i, j, colorData);
//					}
//					else if (typeRepresentation == "Rendu 3D")
//					{
//						Color fractal = Color.red;
//						int rouge = 0, vert = 0, bleu = 0;
//
//						double r = (double)(Infos.InfSin.getAmplitudeR()*Math.sin(
//							Infos.InfSin.getPulsationR()*mode3D + Infos.InfSin.getPhaseR()));
//						double g = (double)(Infos.InfSin.getAmplitudeG()*Math.sin(
//							Infos.InfSin.getPulsationG()*mode3D + Infos.InfSin.getPhaseG()));
//						double bl = (double)(Infos.InfSin.getAmplitudeB()*Math.sin(
//							Infos.InfSin.getPulsationB()*mode3D + Infos.InfSin.getPhaseB()));
//						//System.out.println((int)(rouge*255.99));
//						rouge = (int)(r*255.99) > 255 ? 255 : (int)(r*255.99) < 0 ? 0 : (int)(r*255.99);
//						vert = (int)(g*255.99)> 255 ? 255 : (int)(g*255.99)< 0 ? 0 : (int)(g*255.99);
//						bleu = (int)(bl*255.99)> 255 ? 255 : (int)(bl*255.99)< 0 ? 0 : (int)(bl*255.99);
//
//						fractal = new Color(rouge, vert, bleu);   //On crée la couleur
//
//						argb = fractal.getRGB();
//						colorData = model.getDataElements(argb, null);
//						raster.setDataElements(i, j, colorData);
//					}
//				}
//
//				cpt++;
//				if (cpt == ((largeur*hauteur)*pourcentage) / 100)
//				{
//					Progression.setValue(pourcentage);
//					pourcentage++;
//					//System.out.println(Progression.getValue());
//				}
//			}
//		return image;
//	}
//
//
//}

