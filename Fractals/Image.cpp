#include "Image.h"

#include "Logger.h"
#include "ReconstructionFilter.h"


//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Pixel::applyColor()
{
	if (myWeight != 0.)
	{
		myColor /= myWeight;
		myWeight = 0;
	}

	//myColor.validate();
	//myColor *= 255;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Image::Image(int sizeX, int sizeY, int minX, int minY, ReconstructionFilter::ptr filter)
	:mySizeX(sizeX)
	, mySizeY(sizeY)
	, myMinX(minX)
	, myMinY(minY)
	, myOverlapX(0)
	, myOverlapY(0)
{
	if (filter)
		setFilter(filter);
	else
		myPixels.setSize(sizeX, sizeY);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Image::~Image(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Image::addSample(double xx, double yy, const Color& value)
{
	if (std::isnan(value.r) || std::isnan(value.g) || std::isnan(value.b))
	{
		ILogger::log() << "NaN value\n";
	}

	if (!myFilter)
	{
		xx = xx - myMinX;
		yy = yy - myMinY;

		Pixel& pixel = myPixels((int)xx, (int)yy);
		pixel.myColor += value ;
		pixel.myWeight += 1.;
	}
	else
	{

		//Define the pixel center in the center and not upper left corner, 
		//adjust if to chunk coordinates and consider filter radius
		xx = xx - 0.5f - (myMinX - myOverlapX);
		yy = yy - 0.5f - (myMinY - myOverlapY);


		int startX = (int)std::ceil(xx - myFilter->getRadiusX());
		int endX = (int)std::floor(xx + myFilter->getRadiusX());
		int startY = (int)std::ceil(yy - myFilter->getRadiusY());
		int endY = (int)std::floor(yy + myFilter->getRadiusY());

		startX = std::max(0, startX);
		endX = std::min((int)myPixels.getWidth() - 1, endX);
		startY = std::max(0, startY);
		endY = std::min((int)myPixels.getHeight() - 1, endY);

		for (int x = startX; x <= endX; x++)
		{
			for (int y = startY; y <= endY; y++)
			{
				double weight = (*myFilter)(x - xx, y - yy);
				Pixel& pixel = myPixels(x, y);
				pixel.myColor += value * weight;
				pixel.myWeight += weight;
			}
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Image::setFilter(ReconstructionFilter::ptr filter)
{
	myFilter = filter;

	if (!myFilter)
	{
		myOverlapX = myOverlapY = 0;
	}
	else
	{
		myOverlapX = (int)std::ceil(myFilter->getRadiusX() - 0.5f);
		myOverlapY = (int)std::ceil(myFilter->getRadiusY() - 0.5f);
	}

	myPixels.setSize(mySizeX + 2 * myOverlapX, mySizeY + 2 * myOverlapY);
	//Precompute filter values
	//myFilter->precompute();
}

void Image::postProcessColor()
{
	for (int x = 0; x < mySizeX; x++)
	{
		for (int y = 0; y < mySizeY; y++)
		{
			myPixels(x, y).applyColor();
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::unique_ptr<Image> Image::createSubImage(int sizeX, int sizeY, int minX, int minY)
{
	std::unique_ptr<Image> subScreen(new Image(sizeX, sizeY, minX, minY));
	subScreen->setFilter(myFilter);

	return subScreen;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Image::merge(Image& subScreen)
{
	int offsetX = subScreen.getMinX() - myMinX + myOverlapX - subScreen.getOverlapX();
	int offsetY = subScreen.getMinY() - myMinY + myOverlapY - subScreen.getOverlapY();

	int sizeX = subScreen.getSizeX() + 2 * subScreen.getOverlapX();
	int sizeY = subScreen.getSizeY() + 2 * subScreen.getOverlapY();

	std::lock_guard<std::mutex> lock(myMergeMutex);

	int tmpX = 0;
	for (int x = offsetX; x < offsetX + sizeX; x++)
	{
		int tmpY = 0;
		for (int y = offsetY; y < offsetY + sizeY; y++)
		{
			myPixels(x, y).myColor += subScreen.getPixel(tmpX, tmpY).myColor;
			myPixels(x, y).myWeight += subScreen.getPixel(tmpX, tmpY).myWeight;
			tmpY++;
		}
		tmpX++;
	}
}

void Image::resize(int sizeX, int sizeY, int minX, int minY)
{
	myPixels.setSize(sizeX, sizeY);
	mySizeX = sizeX;
	mySizeY = sizeY;
	myMinX = minX;
	myMinY = minY;
}
