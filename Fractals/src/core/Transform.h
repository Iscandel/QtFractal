#pragma once
#include <Eigen/Core>
#include <Eigen/LU>
#include <Eigen/Geometry>

#include <memory>

#include "core/Maths.h"
#include "core/BaseTypes.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Special 2D affine transform built in the Translation * rotation * scale
/// way. Does not handle projective transforms
///////////////////////////////////////////////////////////////////////////////
class Transform2TRS
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

public:
	typedef std::shared_ptr<Transform2TRS> ptr;
	typedef Eigen::Matrix<real, 3, 3> Matrix3r;

public:
	Transform2TRS(void);
	//Transform2TRS(real* values);
	Transform2TRS(const Matrix3r& transform);
	Transform2TRS(const Matrix3r& transform, const Matrix3r& invTransform);
	~Transform2TRS(void);

	template<class T>
	inline void transform(const T& inPoint, T& outPoint);

	inline Point2r transform(const Point2r& vect);
	inline void transform(const Point2r& in, Point2r& out);

	inline Point3r transform(const Point3r& vect);
	inline void transform(const Point3r& in, Point3r& out);

	//inline Normal3d transform(const Normal3d& n);
	//inline void transform(const Normal3d& inN, Normal3d& outN);

	inline Transform2TRS inv() { return Transform2TRS(myInvMatrix, myMatrix); }

	///Adds a rotation around the origin
	void rotate(real degreeAngle) { myDegreeAngle += degreeAngle; refresh(); }
	void setRotation(real degreeAngle) { myDegreeAngle = degreeAngle; refresh(); }
	real getRotationAngle() const { return myDegreeAngle; }

	void translate(real x, real y) { myTranslation += Point2r(x, y); refresh(); }
	void setTranslation(real x, real y) { myTranslation = Point2r(x, y); refresh(); }
	const Point2r& getTranslation() const { return myTranslation; }

	void scale(real x, real y) { myScale += Point2r(x, y); refresh(); }
	void setScale(const Point2r& s) { myScale = s; refresh(); }
	void setScale(real x, real y) { myScale = Point2r(x, y); refresh(); }
	const Point2r& getScale() const { return myScale; }

	void setFromPositionRotationScale(const Point2r& pos, real angle, const Point2r& scale)
	{
		myTranslation = pos;
		myDegreeAngle = angle;
		myScale = scale;
		refresh();
	}

	static Transform2TRS fromPositionRotationScale(const Point2r& pos, real angle, const Point2r& scale)
	{
		Transform2TRS transform;
		transform.setFromPositionRotationScale(pos, angle, scale);
		return transform;
	}

	void refresh()
	{
		myMatrix.topLeftCorner<2, 2>() = myScale.asDiagonal();
		myMatrix.topLeftCorner<2, 2>() *= makeRotationMatrix(myDegreeAngle);
		myMatrix.col(2).segment(0, 2) = myTranslation;

		myInvMatrix = myMatrix.inverse(); //Could be optimized
	}

	Eigen::Matrix<real, 2, 2> makeRotationMatrix(real degreeAngle) {
		real radAngle = maths::toRadian(degreeAngle);
		real sinA = std::sin(radAngle);
		real cosA = std::cos(radAngle);
		return (Eigen::Matrix<real, 2, 2>() << cosA, -sinA, sinA, cosA).finished();
	}

	//inline Transform<Dim> operator * (const Transform<Dim>& t);
	//inline Transform<Dim>& operator *= (const Transform<Dim>& t);

	static Transform2TRS identity() { return Transform2TRS(Matrix3r::Identity(), Matrix3r::Identity()); }



	///////////////////////////////////////////////////////////////////////////////
	/// \brief Create a translation matrix
	///////////////////////////////////////////////////////////////////////////////

	//template<class T>
	//static Transform translate(const T& t);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Create a scale matrix
	///////////////////////////////////////////////////////////////////////////////
	//static Transform scale(const Point2r s);
	//template<class T>
	//static Transform rotateX(real angle);
	//static Transform rotateY(real angle);
	//static Transform rotateZ(real angle);

	//static Transform fromLookAt(const Point3d& origin, const Point3d& lookAt, const Vector3d& up);

	friend std::ostream& operator << (std::ostream& o, const Transform2TRS& t)
	{
		o << "[" << t.myMatrix << "]";
		return o;
	}

protected:
	real myDegreeAngle;
	Point2r myTranslation;
	Point2r myScale;
	Matrix3r myMatrix;
	Matrix3r myInvMatrix;
};

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
inline Point2r Transform2TRS::transform(const Point2r & point)
{
	Point2r res;
	transform(point, res);
	return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
inline void Transform2TRS::transform(const Point2r & inPoint, Point2r & outPoint)
{
	Point3r p(inPoint(0), inPoint(1), 1);
	outPoint = (myMatrix * p).head<2>();

	//outPoint.x() = myMatrix(0, 0) * inPoint.x() + myMatrix(0, 1) * inPoint.y() + myMatrix(0, 2) * inPoint.z() + myMatrix(0, 3);
	//outPoint.y() = myMatrix(1, 0) * inPoint.x() + myMatrix(1, 1) * inPoint.y() + myMatrix(1, 2) * inPoint.z() + myMatrix(1, 3);
	//outPoint.z() = myMatrix(2, 0) * inPoint.x() + myMatrix(2, 1) * inPoint.y() + myMatrix(2, 2) * inPoint.z() + myMatrix(2, 3);
	//real w = myMatrix(3, 0) * inPoint.x() + myMatrix(3, 1) * inPoint.y() + myMatrix(3, 2) * inPoint.z() + myMatrix(3, 3);

	//if (w != 1. && w != 0.)
	//	outPoint /= w;
}

//typedef Transform2TRS Transform;

////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//inline Point2r Transform2TRS::transform(const Point3r & point)
//{
//	Point3r res;
//	transform(point, res);
//	return res;
//}
//
////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//inline void Transform2TRS::transform(const Point3r & inPoint, Point2r & outPoint)
//{
//	Point3r p(inPoint(0), inPoint(1), 1);
//	outPoint = myMatrix * inPoint;
//}


////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//inline Transform Transform::operator * (const Transform& t)
//{
//	return Transform(myMatrix * t.myMatrix, t.myInvMatrix * myInvMatrix);
//}
//
////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//inline Transform & Transform::operator*=(const Transform & t)
//{
//	myMatrix *= t.myMatrix;
//	myInvMatrix = t.myInvMatrix * myMatrix;
//	return *this;
//}

