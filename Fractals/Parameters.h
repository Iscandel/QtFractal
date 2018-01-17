#pragma once

#include "Color.h"

#include <boost\any.hpp>
#include <map>

template<class Type>
class Property
{
public:
	Property(const std::string& name, Type value) : myName(name), myValue(value) {}
	std::string myName;
	Type myValue;
};

class Parameters
{
public:
	Parameters();
	~Parameters();

	void addInt(const std::string& name, int val);
	void addBool(const std::string& name, bool val);
	void addDouble(const std::string& name, double val);
	//void addPoint(const std::string& name, const Point3d& val);
	void addString(const std::string& name, const std::string& val);
	//void addVector(const std::string& name, const Vector3d& val);
	void addColor(const std::string& name, const Color& val);
	void addVector(const std::string& name, const std::vector<boost::any>& val);
	//void addTransform(const std::string& name, Transform::ptr val);
	//void addBSDF(const std::string& name, BSDF::ptr val);
	//void addLight(const std::string& name, Light::ptr val);
	//void addTexture(const std::string& name, Texture::ptr val);
	

	int getInt(const std::string& name, int defaultValue) const;
	bool getBool(const std::string& name, bool defaultValue) const;
	double getDouble(const std::string& name, double defaultValue) const;
	std::string getString(const std::string& name, const std::string& defaultValue) const;
	//Point3d getPoint(const std::string& name, const Point3d& defaultValue) const;
	std::vector<boost::any> getVector(const std::string& name, const std::vector<boost::any>& defaultValue) const;
	Color getColor(const std::string& name, const Color& defaultValue) const;
	//Transform::ptr getTransform(const std::string& name, Transform::ptr defaultValue) const;
	//BSDF::ptr getBSDF(const std::string& name, BSDF::ptr defaultValue) const;
	//Light::ptr getLight(const std::string& name, Light::ptr defaultValue) const;
	//Texture::ptr getTexture(const std::string& name, Texture::ptr defaultValue) const;

	bool hasInt(const std::string& name) const;
	bool hasBool(const std::string& name) const;
	bool hasDouble(const std::string& name) const;
	bool hasString(const std::string& name) const;
	bool hasPoint(const std::string& name) const;
	bool hasVector(const std::string& name) const;
	bool hasColor(const std::string& name) const;
	bool hasTransform(const std::string& name) const;
	bool hasBSDF(const std::string& name) const;
	bool hasLight(const std::string& name) const;
	bool hasTexture(const std::string& name) const;
	

	//struct Values
	//{
	//	int valInt;
	//	double valDouble;
	//	Point3d valPoint3d;
	//	Vector3d valVector3d;
	//	Transform::ptr valTransform

	//};

protected:
	//Int map
	std::map<std::string, int> myInt;
	//Bool
	std::map<std::string, bool> myBool;	
	//Double
	std::map<std::string, double> myDouble;
	//Point
	//std::map<std::string, Point3d, std::less<std::string>,
	//	Eigen::aligned_allocator<std::pair<const std::string, Point3d>> > myPoint;
	//String
	std::map<std::string, std::string> myString;
	//Vector
	std::map<std::string, std::vector<boost::any>> myVector;
	//Color
	std::map<std::string, Color> myColor;
	//Transform
	//std::map<std::string, Transform::ptr> myTransform;
	//Bsdf
	//std::map<std::string, BSDF::ptr> myBSDF;
	//Light
	//std::map<std::string, Light::ptr> myLight;
	//Texture
	//std::map<std::string, Texture::ptr> myTexture;

};

