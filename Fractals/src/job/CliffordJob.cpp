#include "CliffordJob.h"

#include "fractal/Clifford.h"

CliffordJob::CliffordJob(int offsetX, int offsetY, int sizeX, int sizeY, Clifford* fractal, const Parameters& params, 
	Camera::ptr camera, int maxIt, real scale, Image::ptr imageRes, const Color& col)
	:myOffsetX(offsetX)
	, myOffsetY(offsetY)
	, mySizeX(sizeX)
	, mySizeY(sizeY)
	, myIsFinished(false)
	, myFractal(fractal)
	, myParameters(params)
	//, myImage(image)
	, myCamera(camera.get())
	, myMaxIt(maxIt)
	, myScale(scale)
	, myImageRes(imageRes)
	, myColor(col)
	//, myProgress(0)
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
	int endX = std::min(myImageRes->getSizeX(), myOffsetX + mySizeX);
	int startY = std::max(0, myOffsetY);
	int endY = std::min(myImageRes->getSizeY(), myOffsetY + mySizeY);

	std::unique_ptr<Image> subImage =
		myImageRes->createSubImage(myImageRes->getSizeX(), myImageRes->getSizeY(), 0, 0);


	int oversampling = myParameters.getInt("oversampling", 1);

	for (int y = 0; y < myImageRes->getSizeY(); y++)
	{
		std::cout << y << std::endl;
		for (int x = 0; x < myImageRes->getSizeX(); x++)
		{
			for (int i = 0; i < oversampling; i++)
			{
				for (int j = 0; j < oversampling; j++)
				{
					double xx = (double)x + (double)j / oversampling;
					double yy = (double)y + (double)i / oversampling;
					//for (int i = 0; i < mySampler->getSampleNumber(); i++)
					{
						//new
						Point2r worldPoint = myCamera->getWorldSpacePoint(xx, yy);
						auto trace = myFractal->computePixel(worldPoint(0), worldPoint(1), myMaxIt);

						for (int i = 0; i < trace.size(); i++)
						{
							subImage->addSample(trace[i].x, trace[i].y, myColor);
						}
					}
				}
			}
		}
	}

	Image& tmpImage = (*subImage);
	double maxVal = std::max(tmpImage(0, 0).r, std::max(tmpImage(0, 0).g, tmpImage(0, 0).b));
	for (int i = 0; i < myImageRes->getSizeX(); i++)		//boucle sur tous les pixels de l’image
	{
		for (int j = 0; j < myImageRes->getSizeY(); j++)
		{
			tmpImage.getPixel(i, j).myWeight = 0.;
			maxVal = std::max(maxVal, std::max(tmpImage(i, j).r, std::max(tmpImage(i, j).g, tmpImage(i, j).b)));
		}
	}

	for (int i = 0; i < myImageRes->getSizeX(); i++)		//boucle sur tous les pixels de l’image
	{
		for (int j = 0; j < myImageRes->getSizeY(); j++)
		{

			tmpImage(i, j) /= (maxVal / myScale);
		}
	}

	myImageRes->merge(*subImage);
}