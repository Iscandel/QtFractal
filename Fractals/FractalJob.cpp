#include "FractalJob.h"

#include "MathParser.h"

#include <algorithm>

GenericFractalJob::GenericFractalJob(int offsetX, int offsetY, int sizeX, int sizeY, GenericParallelizableFractal* fractal, const Parameters& params, Image::ptr image)
:myOffsetX(offsetX)
, myOffsetY(offsetY)
, mySizeX(sizeX)
, mySizeY(sizeY)
, myIsFinished(false)
, myFractal(fractal)
, myParameters(params)
, myImage(image)
, myProgress(0)
//,myWidth(width)
//,myHeight(height)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
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

	//Compute the domain point
	const double XMIN = myParameters.getDouble("xmin", -2.);
	const double XMAX = myParameters.getDouble("xmax", 2.);
	const double YMIN = myParameters.getDouble("ymin", -2.);
	const double YMAX = myParameters.getDouble("ymax", 2.);

	int width = myImage->getSizeX();
	int height = myImage->getSizeY();

	//std::map<int, MathParser> parsers;
	//std::map<int, std::string>::iterator it = myParserExprByContext.begin();
	//for (it; it != myParserExprByContext.end(); ++it) {
	//	parsers[it->first] = MathParser(it->second, "zn, zprev, zpprev, c");
	//	//parsers[it->first] = FunctionParser_cd();
	//	//parsers[it->first].Parse(it->second, "z,c");
	//	//parsers[it->first].Optimize();
	//}

	std::map<int, MathParser> parsers;
	//std::string func = myParameters.getString("function", "");
	//if(func != "")
	//	parsers[0] = MathParser(func, "zn, zprev, zpprev, c");

	std::vector<boost::any> vec = myParameters.getVector("parsers", std::vector<boost::any>());
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		MathParser parser = boost::any_cast<MathParser>(vec[i]);
		parsers[parser.getId()] = parser;
	}

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

						//Current point
						double a = XMIN + xx * (XMAX - XMIN) / width;
						double b = YMIN + yy * (YMAX - YMIN) / height;
						Color col = myFractal->computePixel(a, b, myParameters, parsers);

						subScreen->addSample(xx, yy, col);
					}
				}
			}
		}
	}

	std::vector<uint8_t> modifiedData;
	//Merge the subblock with the full screen
	myImage->merge(*subScreen, &modifiedData, true);

	int minX, maxX, minY, maxY;
	subScreen->getTrueImageMinMax(minX, maxX, minY, maxY);
	//minX = std::max(0, startX);
	//maxX = std::min((int)myImage->getSizeX(), endX);
	//minY = std::max(0, startY);
	//maxY = std::min((int)myImage->getSizeY(), endY);

	//uint8_t* tmp = new uint8_t[modifiedData.size()];
	//for (int i = 0; i < modifiedData.size(); i++)
	//	tmp[i] = modifiedData[i];
	//memcpy(tmp, modifiedData.data(), modifiedData.size());
	myProgress.reportDataModified(minX, maxX, minY, maxY, myImage->getOverlapX(), myImage->getOverlapY(), modifiedData);//.data());
}
