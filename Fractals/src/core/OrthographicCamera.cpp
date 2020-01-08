#include "OrthographicCamera.h"



OrthographicCamera::OrthographicCamera()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
OrthographicCamera::~OrthographicCamera()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Point2r OrthographicCamera::getWorldSpacePoint(real x, real y)
{
	//Rescale x and y in the range [-1, 1]
	double a = (x - myWidth / 2.) / (myWidth / 2.); //[-1 1]
	double b = (y - myHeight / 2.) / (myHeight / 2.); //[-1 1]

	//old
	//Eigen::Vector3d vec(a, b, 1);
	//vec = myTransform * vec;

	//return Point2r(vec(0), vec(1));

	return myTransform.transform(Point2r(a, b));
}

Point2r OrthographicCamera::getIndexSpacePoint(real a, real b)
{
	//old
	//Eigen::Vector3d vec(a, b, 1);
	//vec = myTransform.inverse() * vec;

	Point2r vec(a, b);
	vec = myTransform.inv().transform(vec);

	//Rescale x and y in the range [-1, 1]
	//a = (vec(0) - myWidth / 2.) / (myWidth / 2.); //[-1 1]
	//b = (vec(1) - myHeight / 2.) / (myHeight / 2.); //[-1 1]

	double x = vec(0) * (myWidth / 2.) + myWidth / 2.;
	double y = vec(1) * (myHeight / 2.) + myHeight / 2.;

	return Point2r(x, y);
}