#include "ImageUtils.h"

#include "core/Color.h"
#include "Logger.h"
#include "core/Image.h"
#include "core/Maths.h"

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ImageUtils::ImageUtils()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ImageUtils::~ImageUtils()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
int ImageUtils::bytesPerPixelFromFormat(Format format)
{
	int bytesPerPixel;
	if (format == RGB32)
		bytesPerPixel = 4;
	else if (format == ARGB32)
		bytesPerPixel = 4;
	else if (format == RGBA32)
		bytesPerPixel = 4;
	else
		ILogger::log(ILogger::ERRORS) << "Unrecognized format\n";

	return bytesPerPixel;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ImageUtils::convert(const std::vector<uint8_t>& source, int sourceBytesPerPixel, int minX, int maxX, int minY, int maxY, 
	int overlapX, int overlapY,	int imageSizeX, int imageSizeY, std::vector<uint32_t>& dest, Format format)
{
	int bytesPerPixel = bytesPerPixelFromFormat(format);

	//source block size
	int blockSize = maxX - minX;

	//Due to borders, the "overlap" first and last pixels should not be taken into account
	if (minX < overlapX)
		maxX -= overlapX;
	else if (maxX > imageSizeX)
		maxX = imageSizeX;
	else //central blocks are fully copied with 
		overlapX = 0;
	if (minY < overlapY)
		maxY -= overlapY;
	else if (maxY > imageSizeY)
		maxY = imageSizeY;
	else
		overlapY = 0;

	//std::lock_guard<std::mutex> lock(myRefreshMutex);

	int tmpY = 0;
	for (int y = minY; y < maxY; y++)
	{
		int tmpX = 0;
		for (int x = minX; x < maxX; x++)
		{
			uint32_t intCol = numberColorFromFormat<uint32_t>(format,
				(uint8_t)0xff,
				source[((tmpY + overlapY) * blockSize + (tmpX + overlapX)) * sourceBytesPerPixel],
				source[((tmpY + overlapY) * blockSize + (tmpX + overlapX)) * sourceBytesPerPixel + 1],
				source[((tmpY + overlapY) * blockSize + (tmpX + overlapX)) * sourceBytesPerPixel + 2]);

			//dest[(y * imageSizeX + x) * bytesPerPixel] = intCol;
			dest[(y * imageSizeX + x)] = intCol;
			
			tmpX++;
		}
		tmpY++;
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ImageUtils::convert(const Array2D<Pixel>& source, int overlapX, int overlapY,
	int imageSizeX, int imageSizeY, std::vector<uint32_t>& dest, Format format)
{

	//std::lock_guard<std::mutex> lock(myRefreshMutex);
	for (int i = 0; i < imageSizeX; i++)
	{
		for (int j = 0; j < imageSizeY; j++)
		{
			//const Color& col = myArray(i, j);
			const Pixel& col = source(i + overlapX, j + overlapY);
			uint32_t intCol = numberColorFromFormat<uint32_t>(format,
				(uint8_t)0xff,
				(uint8_t)maths::thresholding<int>(col.myColor.r * 255., 0, 255),
				(uint8_t)maths::thresholding<int>(col.myColor.g * 255., 0, 255),
				(uint8_t)maths::thresholding<int>(col.myColor.b * 255., 0, 255));

			dest[(j * imageSizeX + i)] = intCol;
		}
	}
}