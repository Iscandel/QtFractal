#include "FractalJob.h"

#include <algorithm>

GenericFractalJob::GenericFractalJob(int offsetX, int offsetY, int sizeX, int sizeY, GenericParallelizableFractal* fractal, const Parameters& params, Image::ptr image)
:myOffsetX(offsetX)
,myOffsetY(offsetY)
,mySizeX(sizeX)
,mySizeY(sizeY)
,myIsFinished(false)
,myFractal(fractal)
,myParameters(params)
,myImage(image)
//,myWidth(width)
//,myHeight(height)
{
}


GenericFractalJob::~GenericFractalJob()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GenericFractalJob::run()
{
	//myFractal->compute(myParameters);

	int startX = std::max(0, myOffsetX);
	int endX = std::min(myImage->getSizeX(), myOffsetX + mySizeX);
	int startY = std::max(0, myOffsetY);
	int endY = std::min(myImage->getSizeY(), myOffsetY + mySizeY);

	std::unique_ptr<Image> subScreen =
		myImage->createSubImage(endX - startX, endY - startY, myOffsetX, myOffsetY);

	int oversampling = myParameters.getInt("oversampling", 1);

	for (int y = myOffsetY; y < endY; y++)
	{
		//std::cout << y << std::endl;
		for (int x = myOffsetX; x < endX; x++)
		{
			//std::cout << "x " << x << std::endl;
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
						int width = myImage->getSizeX();
						int height = myImage->getSizeY();

						//On calcule le point courant. Il est situ� entre XMIN et XMAX (resp. YMIN et YMAX),
						//et il y a largeur points entre XMIN et XMAX (resp. longueur points entre YMIN etYMAX)
						double a = XMIN + xx * (XMAX - XMIN) / width;
						double b = YMIN + yy * (YMAX - YMIN) / height;
						Color col = myFractal->computePixel(a, b, myParameters);

						subScreen->addSample(xx, yy, col);
					}
				}
			}
		}
	}

	//Merge the subblock with the full screen
	myImage->merge(*subScreen);
}