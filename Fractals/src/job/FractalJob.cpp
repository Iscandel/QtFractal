#include "FractalJob.h"

#include "core/MathParser.h"

#define _USE_MATH_DEFINES

#include <algorithm>
#include <math.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

GenericFractalJob::GenericFractalJob(int offsetX, int offsetY, int sizeX, int sizeY, GenericParallelizableFractal* fractal, const Parameters& params, Image::ptr image, Camera::ptr camera)
:myOffsetX(offsetX)
, myOffsetY(offsetY)
, mySizeX(sizeX)
, mySizeY(sizeY)
, myIsFinished(false)
, myFractal(fractal)
, myParameters(params)
, myImage(image)
, myCamera(camera)
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
	const double ANGLE = myParameters.getDouble("angle", 0.); //invert angle...

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

	//ok
	double theta = ANGLE * M_PI / 180.;
	double scaleX = myParameters.getDouble("scaleX", 2.);
	double scaleY = myParameters.getDouble("scaleY", 2.);
	double cx = myParameters.getDouble("centerX", 0.);
	double cy = myParameters.getDouble("centerY", 0.);
	Eigen::Vector2d center(cx, cy);
	Eigen::Affine2d affine = Eigen::Affine2d::Identity();
	affine.prescale(Eigen::Vector2d(scaleX, scaleY));
	affine.prerotate(-theta);
	affine.pretranslate(center);


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
						
						//double scaleX = (XMAX - XMIN) / width;
						//double scaleY = (YMAX - YMIN) / height;
						//double theta = ANGLE * M_PI / 180.;
						//double cosTheta = std::cos(theta);
						//double sinTheta = std::sin(theta);
						//double r00 = cosTheta ; double r01 = sinTheta ; double r10 = -sinTheta ; double r11 = cosTheta ;
						//double centerX = -(XMAX + XMIN) / 2.;
						//double centerY = -(YMAX + YMIN) / 2.;
						//double tx = -(r00 * centerX + r01 * centerY);
						//double ty = -(r10 * centerX + r11 * centerY);
						//Eigen::Affine2d affine;
						//affine.translate(Eigen::Vector2d(-centerX, -centerY));
						//affine.prerotate(Eigen::Rotation2D<double>(theta));
						//auto transform = affine.inverse();

						//Eigen::Vector3d origin(-centerX, -centerY, 1);
						//Eigen::Vector3d up(std::cos(-(theta-M_PI/2.)), std::sin(-(theta-M_PI/2.)), 0);
						//Eigen::Vector3d dir(0, 0, 1);
						//Eigen::Vector3d left = (up.normalized().cross(dir)).normalized();
						//Eigen::Vector3d newUp = dir.cross(left).normalized();
						//Eigen::Matrix<double, 4, 4> trafo;

						//trafo << left, newUp, dir, origin, 0, 0, 0, 1;
						//Eigen::Matrix<double, 3, 3> transfo2;
						//transfo2.topLeftCorner<2, 2>() = trafo.topLeftCorner<2, 2>();
						//auto tmp = trafo.col(3);//.segment(0, 2);
						//transfo2(0, 2) = trafo(0, 3);
						//transfo2(1, 2) = trafo(1, 3);
						//transfo2(2, 2) = 1;
						//r00 = transfo2(0, 0), r01 = transfo2(0, 1), r10 = transfo2(1, 0), r11 = transfo2(1, 1);
						//tx = transfo2(0, 2), ty = transfo2(1, 2);
						
						//correct
						//double centerX = -(XMAX + XMIN) / 2.;
						//double centerY = -(YMAX + YMIN) / 2.;
						//Eigen::Affine2d affine = Eigen::Affine2d::Identity();
						//affine.pretranslate(Eigen::Vector2d(centerX, centerY));
						////double theta = ANGLE * M_PI / 180.;
						//affine.prerotate(Eigen::Rotation2D<double>(-theta));
						//affine.pretranslate(Eigen::Vector2d(-centerX, -centerY));

						//new
						Point2r worldPoint = myCamera->getWorldSpacePoint(xx, yy);
						real a = worldPoint(0);
						real b = worldPoint(1);
						Color col = myFractal->computePixel(a, b, myParameters, parsers);

						//double a = (xx - width / 2.) / (width / 2.); //[-1 1]
						//double b = (yy - height / 2.) / (height / 2.); //[-1 1]


						////double a = (xx - width / 2.) * r00 * scaleX + (yy - height / 2.) * r01 * scaleX + tx ;
						////double b = (xx - width / 2.) * r10 * scaleY + (yy - height / 2.) * r11 * scaleY+ ty;
						////double a = XMIN + xx * (XMAX - XMIN) / width;
						////double b = YMIN + yy * (YMAX - YMIN) / height;

						//Eigen::Vector3d vec(a, b, 1);
						//vec = affine * vec;
						//a = vec(0); b = vec(1);

						//Color col = myFractal->computePixel(a, b, myParameters, parsers);

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
