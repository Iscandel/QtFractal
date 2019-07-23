#pragma once
#include "Array2D.h"
#include "Image.h"
#include "Logger.h"

#include <stdint.h>
#include <vector>

class ImageUtils
{
public:
	enum Format
	{
		RGB32,
		ARGB32,
		RGBA32
	};

public:
	ImageUtils();
	~ImageUtils();

	static void convert(const std::vector<uint8_t>& source, int sourceBytesPerPixel, int minX, int maxX, int minY, int maxY, 
		int overlapX, int overlapY,	int imageSizeX, int imageSizeY, std::vector<uint32_t>& dest, Format format);

	static void convert(const Array2D<Pixel>& source, int overlapX, int overlapY,
		int imageSizeX, int imageSizeY, std::vector<uint32_t>& dest, Format format);

	template<class T>
	static T numberColorFromFormat(Format format, int a, int r, int g, int b);

	static int bytesPerPixelFromFormat(Format format);
};

template<class T>
T ImageUtils::numberColorFromFormat(Format format, int a, int r, int g, int b)
{
	T intColor;
	if (format == RGB32)
		intColor = Color::toARGB32(0xff, r, g, b);
	else if (format == ARGB32)
		intColor = Color::toARGB32(a, r, g, b);
	else if (format == RGBA32)
		intColor = Color::toRGBA32(r, g, b, a);
	else
		ILogger::log(ILogger::ERRORS) << "Unrecognized format\n";

	return intColor;
}