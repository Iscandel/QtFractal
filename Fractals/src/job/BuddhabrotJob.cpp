#include "BuddhabrotJob.h"

#include "fractal/Buddhabrot.h"

BuddhabrotJob::BuddhabrotJob(int offsetX, int offsetY, int sizeX, int sizeY, Buddhabrot* fractal, const Parameters& params, Image::ptr imageRed, Image::ptr imageGreen, Image::ptr imageBlue)//Image::ptr image)
:myOffsetX(offsetX)
,myOffsetY(offsetY)
,mySizeX(sizeX)
,mySizeY(sizeY)
,myIsFinished(false)
,myFractal(fractal)
,myParameters(params)
,myImageRed(imageRed)
,myImageGreen(imageGreen)
,myImageBlue(imageBlue)
//,myImage(image)
{
}


BuddhabrotJob::~BuddhabrotJob()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BuddhabrotJob::run()
{
	int startX = std::max(0, myOffsetX);
	int endX = std::min(myImageRed->getSizeX(), myOffsetX + mySizeX);
	int startY = std::max(0, myOffsetY);
	int endY = std::min(myImageRed->getSizeY(), myOffsetY + mySizeY);

	//old
	//int startX = std::max(0, myOffsetX);
	//int endX = std::min(myImage->getSizeX(), myOffsetX + mySizeX);
	//int startY = std::max(0, myOffsetY);
	//int endY = std::min(myImage->getSizeY(), myOffsetY + mySizeY);

	std::unique_ptr<Image> imageRed =
		myImageRed->createSubImage(myImageRed->getSizeX(), myImageRed->getSizeY(), 0, 0);
	std::unique_ptr<Image> imageGreen =
		myImageGreen->createSubImage(myImageGreen->getSizeX(), myImageGreen->getSizeY(), 0, 0);
	std::unique_ptr<Image> imageBlue =
		myImageBlue->createSubImage(myImageBlue->getSizeX(), myImageBlue->getSizeY(), 0, 0);
	//std::unique_ptr<Image> imageRes =
	//	myImage->createSubImage(myImage->getSizeX(), myImage->getSizeY(), 0, 0);

	//single thread
	//Array2D<double> imageRed(myImage->getSizeX(), myImage->getSizeY());
	//Array2D<double> imageGreen(myImage->getSizeX(), myImage->getSizeY());
	//Array2D<double> imageBlue(myImage->getSizeX(), myImage->getSizeY());
	//Array2D<double> imageRes(myImage->getSizeX(), myImage->getSizeY());


	int oversampling = myParameters.getInt("oversampling", 1);

	//!!!!
	//Transposition of the image to rotate correctly the buddhabrot (offsetY for X and vice-versa)
	//!!!!
	for (int y = myOffsetY; y < endY; y++)
	{
		for (int x = myOffsetX; x < endX; x++)
		{
			for (int i = 0; i < oversampling; i++)
			{
				for (int j = 0; j < oversampling; j++)
				{
					double xx = (double)x + (double)j / oversampling;
					double yy = (double)y + (double)i / oversampling;
					//for (int i = 0; i < mySampler->getSampleNumber(); i++)
					{
						//Point2d sample = mySampler->getNextSample2D();

						//double xx = (double)x;// +sample.x();
						//double yy = (double)y;// +sample.y();

						//Compute the domain point
						const double XMIN = myParameters.getDouble("xmin", -2.);
						const double XMAX = myParameters.getDouble("xmax", 2.);
						const double YMIN = myParameters.getDouble("ymin", -2.);
						const double YMAX = myParameters.getDouble("ymax", 2.);
						int width = myImageRed->getSizeX();
						int height = myImageRed->getSizeY();

						//On calcule le point courant. Il est situé entre XMIN et XMAX (resp. YMIN et YMAX),
						//et il y a largeur points entre XMIN et XMAX (resp. longueur points entre YMIN etYMAX)
						double a = XMIN + xx * (XMAX - XMIN) / width;
						double b = YMIN + yy * (YMAX - YMIN) / height;
						std::vector<std::vector<TraceSample>> trace = myFractal->computePixel(a, b, myParameters);

						Color col(1., 1., 1.);
						for (int i = 0; i < trace[0].size(); i++)
						{
							imageRed->addSample(trace[0][i].x, trace[0][i].y, col);
							//imageRed((int)trace[0][i].x, (int)trace[0][i].y) += 1;
						}
						for (int i = 0; i < trace[1].size(); i++)
						{
							imageGreen->addSample(trace[1][i].x, trace[1][i].y, col);
							//imageGreen((int)trace[1][i].x, (int)trace[1][i].y) += 1;
						}
						for (int i = 0; i < trace[2].size(); i++)
						{
							imageBlue->addSample(trace[2][i].x, trace[2][i].y, col);		
							//imageBlue((int)trace[2][i].x, (int)trace[2][i].y) += 1;
						}
					}
				}
			}
		}
	}

	//for (int y = 0; y < myImage->getSizeY(); y++)
	//{
	//	for (int x = 0; x < myImage->getSizeX(); x++)
	//	{
	//		(*myImage)(x, y) = Color(imageRed(x, y), imageGreen(x, y), imageBlue(x, y));
	//	}
	//}

	//for (int y = 0; y < myImage->getSizeY(); y++)
	//{
	//	for (int x = 0; x < myImage->getSizeX(); x++)
	//	{
	//		double weight = 0;
	//		if (imageRed->getPixel(x, y).myWeight != 0)
	//			weight = imageRed->getPixel(x, y).myWeight;
	//		else if (imageGreen->getPixel(x, y).myWeight != 0)
	//			weight = imageGreen->getPixel(x, y).myWeight;
	//		else if (imageBlue->getPixel(x, y).myWeight != 0)
	//			weight = imageBlue->getPixel(x, y).myWeight;
	//		else
	//			continue;

	//		Color col(
	//			imageRed->getPixel(x, y).myWeight == 0 ? 0 : (*imageRed)(x, y).r * weight / imageRed->getPixel(x, y).myWeight,
	//			imageGreen->getPixel(x, y).myWeight == 0 ? 0 : (*imageGreen)(x, y).g * weight / imageGreen->getPixel(x, y).myWeight,
	//			imageBlue->getPixel(x, y).myWeight == 0 ? 0 : (*imageBlue)(x, y).b * weight / imageBlue->getPixel(x, y).myWeight);
	//		imageRes->getPixel(x, y).myColor = col;

	//		if (!col.isZero() && (col.r != col.b || col.g != col.b))
	//			std::cout << weight << " " << col << std::endl;
	//		imageRes->getPixel(x, y).myWeight = weight;
	//	}
	//}


	////Merge the subblock with the full screen
	//myImage->merge(*imageRes);

	myImageRed->merge(*imageRed);
	myImageGreen->merge(*imageGreen);
	myImageBlue->merge(*imageBlue);
}