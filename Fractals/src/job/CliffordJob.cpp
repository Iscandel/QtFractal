#include "CliffordJob.h"

#include "fractal/Clifford.h"

CliffordJob::CliffordJob(int offsetX, int offsetY, int sizeX, int sizeY, Clifford* fractal, const Parameters& params, Image::ptr imageRed, Image::ptr imageGreen, Image::ptr imageBlue)//Image::ptr image)
	:myOffsetX(offsetX)
	, myOffsetY(offsetY)
	, mySizeX(sizeX)
	, mySizeY(sizeY)
	, myIsFinished(false)
	, myFractal(fractal)
	, myParameters(params)
	, myImageRed(imageRed)
	, myImageGreen(imageGreen)
	, myImageBlue(imageBlue)
{
}


CliffordJob::~CliffordJob()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void CliffordJob::run()
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
					}
				}
			}
		}
	}
}