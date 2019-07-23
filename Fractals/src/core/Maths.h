#pragma once
namespace maths
{
	template<class T>
	T thresholding(T val, T min, T max)
	{
		return val < min ? min : val  > max ? max : val;
	}
};

