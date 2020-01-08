#include "Transform.h"

Transform2TRS::Transform2TRS()
	:myDegreeAngle((real)0)
	,myScale(0,0)
	,myTranslation(0,0)
{
	myMatrix.setIdentity();
	refresh();
}

//Transform2TRS(real* values);
Transform2TRS::Transform2TRS(const Matrix3r& transform)
	:myMatrix(transform)
{
	Eigen::Affine2d eigenTransform(transform);

	Eigen::Matrix2d scale;
	Eigen::Matrix2d mRot;

	eigenTransform.computeRotationScaling(&mRot, &scale);
	Eigen::Vector2d translation = eigenTransform.translation();
	Eigen::Rotation2D<real> rot;
	rot.fromRotationMatrix(mRot);

	myDegreeAngle = maths::toDegre(rot.angle());
	myScale = Point2r(scale.diagonal());
	myTranslation = translation;
}

Transform2TRS::Transform2TRS(const Matrix3r& transform, const Matrix3r& invTransform)
	:myMatrix(transform)
	,myInvMatrix(invTransform)
{
	Eigen::Affine2d eigenTransform(transform);

	Eigen::Matrix2d scale;
	Eigen::Matrix2d mRot;

	eigenTransform.computeRotationScaling(&mRot, &scale);
	Eigen::Vector2d translation = eigenTransform.translation();
	Eigen::Rotation2D<real> rot;
	rot.fromRotationMatrix(mRot);

	myDegreeAngle = maths::toDegre(rot.angle());
	myScale = Point2r(scale.diagonal());
	myTranslation = translation;
}

Transform2TRS::~Transform2TRS()
{

}
