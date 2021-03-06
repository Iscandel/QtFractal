#pragma once
#include "Array2D.h"
#include "Color.h"
#include "filter/ReconstructionFilter.h"

#include <memory>
#include <mutex>

class ReconstructionFilter;

///////////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////////
class Pixel
{
public:
	Pixel() : myWeight(0) {}
	void applyColor();

	//protected:
	Color myColor;
	double myWeight;
};

///////////////////////////////////////////////////////////////////////////////
/// \brief This class reconstructs pixels (and then stores them) from provided 
/// samples interpolated thanks to the specified reconstructions filter
///////////////////////////////////////////////////////////////////////////////
class Image
{
public:
	typedef std::shared_ptr<Image> ptr;

public:
	Image(int sizeX, int sizeY, int minX = 0, int minY = 0, ReconstructionFilter::ptr filter = nullptr);
	~Image(void);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a new sample with the given value, at the given coordinates
	///////////////////////////////////////////////////////////////////////////
	void addSample(double x, double y, const Color& value);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a new reconstruction filter
	///////////////////////////////////////////////////////////////////////////
	void setFilter(ReconstructionFilter::ptr filter);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Utility function to access pixel values
	///////////////////////////////////////////////////////////////////////////
	Color& operator() (int x, int y) { return myPixels(x, y).myColor; }

	const Color& operator() (int x, int y) const { return myPixels(x, y).myColor; }

	///////////////////////////////////////////////////////////////////////////
	/// \brief Computes the final pixel values when all the samples have been 
	/// provided
	///////////////////////////////////////////////////////////////////////////
	void postProcessColor();

	///////////////////////////////////////////////////////////////////////////
	/// \brief 
	///////////////////////////////////////////////////////////////////////////
	std::unique_ptr<Image> createSubImage(int sizeX, int sizeY, int minX, int minY);

	///////////////////////////////////////////////////////////////////////////
	/// \brief 
	///////////////////////////////////////////////////////////////////////////
	void merge(Image& subScreen, std::vector<uint8_t>* modifiedData = nullptr, bool rowMajor = true);

	///////////////////////////////////////////////////////////////////////////
	/// \brief 
	///////////////////////////////////////////////////////////////////////////
	Pixel& getPixel(int x, int y) { return myPixels(x, y); }

	const Pixel& getPixel(int x, int y) const { return myPixels(x, y); }

	Array2D<Pixel>& getPixels() { return myPixels; }

	const Array2D<Pixel>& getPixels() const { return myPixels; }

	int getMinX() const { return myMinX; }
	int getMinY() const { return myMinY; }

	int getOverlapX() const { return myOverlapX; }
	int getOverlapY() const { return myOverlapY; }

	int getSizeX() const { return mySizeX; }
	int getSizeY() const { return mySizeY; }

	void getTrueImageMinMax(int& minX, int& maxX, int& minY, int& maxY);

	void resize(int x, int y, int minX = 0, int minY = 0);

protected:
	Array2D<Pixel> myPixels;
	//Pixel** myPixels;

	int myMinX;
	int myMinY;
	int mySizeX;
	int mySizeY;

	int myOverlapX;
	int myOverlapY;

	std::mutex myMergeMutex;

	ReconstructionFilter::ptr myFilter;
};

