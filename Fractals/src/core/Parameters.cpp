#include "Parameters.h"

//my##TypeName.insert(std::make_pair(name, val)); 
#define CREATE_PARAM_FUNC(typeArg, returnType, TypeName) \
void Parameters::add##TypeName(const std::string& name, typeArg val) \
{\
	my##TypeName[name] =  val; \
} \
\
returnType Parameters::get##TypeName(const std::string& name, typeArg defaultValue) const\
{ \
	std::map<std::string, returnType>::const_iterator it = my##TypeName.find(name); \
	if(it != my##TypeName.end()) \
	{\
		return it->second; \
	} \
	else \
	{ \
		return defaultValue; \
	} \
}\
bool Parameters::has##TypeName(const std::string& name) const\
{ \
	std::map<std::string, returnType>::const_iterator it = my##TypeName.find(name); \
	return (it != my##TypeName.end()); \
} 


Parameters::Parameters()
{

}

Parameters::~Parameters()
{
}

CREATE_PARAM_FUNC(bool, bool, Bool)
CREATE_PARAM_FUNC(int, int, Int)
CREATE_PARAM_FUNC(double, double, Double)
CREATE_PARAM_FUNC(const std::string&, std::string, String)
//CREATE_PARAM_FUNC(const Point3d&, Point3d, Point)
CREATE_PARAM_FUNC(const std::vector<std::any>&, std::vector<std::any>, Vector)
CREATE_PARAM_FUNC(const Color&, Color, Color)
CREATE_PARAM_FUNC(const Transform&, Transform, Transform)
