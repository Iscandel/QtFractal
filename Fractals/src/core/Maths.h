#pragma once

typedef double real;

namespace maths
{
	const real PI = 3.14159265358979323846;
	const real INV_PI = 0.3183098861837906715377;
	const real INV_FOUR_PI = 0.07957747154594766788450883936693;
	const real MAX_REAL = 10e9;
	const real EPSILON = 1e-4;
	const real ONE_MINUS_EPS = 0.99999999999999989;


	inline real toRadian(real degres)
	{
		return (degres * maths::PI) / (real)180.;
	}

	inline real toDegre(real radian)
	{
		return (radian * (real)180.) / maths::PI;
	}

	template<typename T>
	T min(T a) {
		return a;
	}

	template<typename T, typename... Args>
	T min(T first, Args... args) {
		return std::min(first, min(args...));
	}

	template<typename T>
	T max(T a) {
		return a;
	}

	template<typename T, typename... Args>
	T max(T first, Args... args) {
		return std::max(first, max(args...));
	}
	template<class T>
	T thresholding(T val, T min, T max)
	{
		return val < min ? min : val  > max ? max : val;
	}
};

