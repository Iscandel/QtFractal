//#include "Buddhabrot.h"
//
//
//
//Buddhabrot::Buddhabrot()
//{
//}
//
//
//Buddhabrot::~Buddhabrot()
//{
//}
//
//Color Buddhabrot::computePixel(double a, double b, const Parameters& params)
//{
//
///*On alloue une taille de tableau équivalente à la taille de l'image pour chacun des 3 tableaux*/
//lesPointsR = new long[largeur][hauteur];
//lesPointsG = new long[largeur][hauteur];
//lesPointsB = new long[largeur][hauteur];
//
//
//int cpt = 0;
//int pourcentage = 1;
//Progression.setValue(0);
//
///* On boucle 3 fois. Le principe est que chaque tour de boucle va calculer
//* la valeur d'une composante pour chaque pixel de l'image: rouge, puis verte
//*  puis bleue. A la fin des 3 passages, on crée une couleur avec les 3 composantes,
//*  et ce pour chaque pixel. C'est le principe des images en fausse couleur*/
//for (int composante = 0; composante < 3; composante++)
//{
//	/*On recalcule les itérations à chaque passage. Elles doivent normalement
//	* être différentes*/
//	if (composante == 1) maxIterations = Infos.getIterVert()*Infos.getIterations();
//	if (composante == 2) maxIterations = Infos.getIterBleu()*Infos.getIterations();
//	//  maxIterations = maxIterations*2;
//	//System.out.println(maxIterations);
//	pourcentage = 1;
//	Progression.setValue(0);
//	cpt = 0;
//
//	for (int i = 0; i <largeur * 10; i++)		//boucle sur tous les pixels de l’image
//		for (int j = 0; j < hauteur * 10; j++)
//		{
//			if (Stop.getStop())
//			{
//				i = largeur - 1;
//				j = hauteur - 1;
//				JOptionPane.showMessageDialog(null,
//					"Interruption du calcul.", "Information",
//					JOptionPane.INFORMATION_MESSAGE);
//			}
//
//			double a = XMIN + i * (XMAX - XMIN) / (largeur * 10);
//			double b = YMIN + j * (YMAX - YMIN) / (hauteur * 10);
//
//			/*Si le point ne diverge pas, on réappelle la fonction*/
//			if (escapesToInfinity(a, b, false, composante))
//			{
//				escapesToInfinity(a, b, true, composante);
//			}
//
//			cpt++;
//			if (cpt >= ((largeur*hauteur * 10 * 10)*pourcentage) / 100)
//			{
//				Progression.setValue(pourcentage);
//				pourcentage++;
//				System.out.println(Progression.getValue());
//			}
//		}
//	if (composante == 0)  //Si première composante
//	{
//		maxR = lesPointsR[0][0];      //On cherche le max du tableau  
//		for (int i1 = 0; i1 <largeur; i1++)		//boucle sur tous les pixels de l’image
//		{
//			for (int j1 = 0; j1 < hauteur; j1++)
//			{
//				maxR = Math.max(maxR, lesPointsR[i1][j1]);
//			}
//		}
//		coeffR = 255.0 / maxR;   //On le normalise par 1/255
//	}
//
//	if (composante == 1)
//	{
//		maxG = lesPointsG[0][0];
//		for (int i1 = 0; i1 <largeur; i1++)		//boucle sur tous les pixels de l’image
//		{
//			for (int j1 = 0; j1 < hauteur; j1++)
//			{
//				maxG = Math.max(maxG, lesPointsG[i1][j1]);
//			}
//		}
//		coeffG = 255.0 / maxG;
//	}
//
//	if (composante == 2)
//	{
//		maxB = lesPointsB[0][0];
//		for (int i1 = 0; i1 <largeur; i1++)		//boucle sur tous les pixels de l’image
//		{
//			for (int j1 = 0; j1 < hauteur; j1++)
//			{
//				maxB = Math.max(maxB, lesPointsB[i1][j1]);
//			}
//		}
//		coeffB = 255.0 / maxB;
//	}
//
//
//
//
//}//fin composante
//
//for (int i = 0; i <largeur; i++)		//boucle sur tous les pixels de l’image
//{
//	for (int j = 0; j < hauteur; j++)
//	{
//
//		double t1 = lesPointsR[j][i] / (maxR / Infos.getLumiere());
//		if (t1 > 1)
//			t1 = 1;
//		double t2 = lesPointsG[j][i] / (maxG / Infos.getLumiere());
//		if (t2 > 1)
//			t2 = 1;
//		double t3 = lesPointsB[j][i] / (maxB / Infos.getLumiere());
//		if (t3 > 1)
//			t3 = 1;
//
//		Color fractal = new Color((t1),(t2), (t3));
//
//		return 
//	}
//}
//return image;
//	   }
//
//	   bool Buddhabrot::escapesToInfinity(double a, double b, bool passage2, int composante)
//	   {
//		   double x = 0.0;
//		   double y = 0.0;
//		   int iterations = 0;  //On fixe le nombre d'itérations à 0
//		   do
//		   {
//			   double xnew = x * x - y * y + a;
//			   double ynew = 2 * x * y + b;
//			   x = xnew;
//			   y = ynew;
//
//			   if (passage2 == true && iterations >= 2)
//			   {
//				   int n = (int)(((x - XMIN)*width) / (XMAX - XMIN));
//				   int m = (int)(((y - YMIN)*height) / (YMAX - YMIN));
//				   if (x > XMIN && x < XMAX && y > YMIN && y < YMAX)
//				   {
//					   if (composante == 0) lesPointsR[n][m]++;
//					   if (composante == 1) lesPointsG[n][m]++;
//					   if (composante == 2) lesPointsB[n][m]++;
//				   }
//			   }
//
//			   iterations++;
//			   if (iterations == maxIterations) return false;
//		   } while (x*x + y*y <= 4);// <= 2 && y <= 2);
//		   return true;
//	   }
//
//}