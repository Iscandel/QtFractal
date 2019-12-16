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

	Eigen::Vector3d vec(a, b, 1);
	vec = myTransform * vec;

	return Point2r(vec(0), vec(1));
}