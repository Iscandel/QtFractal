#pragma once

#include <iostream>
template<class T>
class Complex
{
public:
	explicit Complex(T _re= (T)0, T _im = (T)0)
		:re(_re)
		, im(_im)
	{
	}
	
	//~Complex();

	T abs(){
		return std::sqrt(re*re + im*im);
	}

	T sqrAbs(){
		return re*re + im*im;
	}

	Complex<T> pow(T power) {
		Complex<T> tmp = *this;
		unsigned int count = power;

		if (power < 0)
			count = 0 - count;	// safe negation as unsigned

		for (Complex<T> _Zv = Complex<T>(1., 0.); ; tmp *= tmp)
		{	// fold in _Left ^ (2 ^ _Count) as needed
			if ((count & 1) != 0)
				_Zv *= tmp;
			if ((count >>= 1) == 0)
				return (power < 0 ? Complex<T>(1, 0) / _Zv : _Zv);
		}
	}

	T re;
	T im;
};

template<class T>
std::ostream& operator << (std::ostream& o, const Complex<T>& z)
{
	o << "[" << z.re << " " << z.im << "]" << std::endl;

	return o;
}

template<class T>
bool operator == (const Complex<T>& z1, const Complex<T>& z2)
{
	return (z1.re == z2.re && z1.im == z2.im);
}

template<class T>
bool operator != (const Complex<T>& c1, const Complex<T>& c2)
{
	return !(c1 == c2);
}

template<class T>
Complex<T> operator + (const Complex<T>& c1, const Complex<T>& c2)
{
	Complex<T> res;
	res.re = c1.re + c2.re;
	res.im = c1.im + c2.im;
	
	return res;
}

template<class T>
Complex<T>& operator += (Complex<T>& c1, const Complex<T>& c2)
{
	return c1 = c1 + c2;
}

template<class T>
Complex<T> operator - (const Complex<T>& c1, const Complex<T>& c2)
{
	Complex<T> res;
	res.re = c1.re - c2.re;
	res.im = c1.im - c2.im;

	return res;
}

template<class T>
Complex<T> operator - (const Complex<T>& c1)
{
	Complex<T> res;
	res.re = -res.re;
	res.im = -res.im;

	return res;
}

template<class T>
Complex<T>& operator -= (Complex<T>& z1, const Complex<T>& z2)
{
	return z1 = z1 - z2;
}

template<class T>
Complex<T> operator * (const Complex<T>& z1, const Complex<T>& z2)
{
	Complex<T> z;
	
	z.re = z1.re*z2.re - z1.im*z2.im;
	z.im = z1.re*z2.im + z1.im*z2.re;

	return z;
}

template<class T>
Complex<T>& operator *= (Complex<T>& c1, const Complex<T>& c2)
{
	return c1 = c1 * c2;
}

template<class T>
Complex<T>& operator *= (Complex<T>& c1, T val)
{
	return c1 = c1 * val;
}

template<class T>
Complex<T> operator *(const Complex<T>& other, T value)
{
	Complex<T> res;
	res.re = other.re * value
	res.im = other.im * value;

	return res;
}

template<class T>
Complex<T> operator *(T value, const Complex<T>& other)
{
	return other * value;
}

template<class T>
Complex<T> operator /(const Complex<T>& z1, const Complex<T>& z2)
{
	Complex<T> z;

	z.re = (z1.re*z2.re + z1.im*z2.im) / (z2.re*z2.re + z2.im*z2.im);
	z.im = (z1.im*z2.re - z1.re*z2.im) / (z2.re*z2.re + z2.im*z2.im);
	
	return z;
}

template<class T>
Complex<T> operator /(T value, const Complex<T>& other)
{
	Complex<T> z;

	z.re = other.re / value;
	z.im = other.im / value;

	return z;
}

template<class T>
Complex<T> operator /(const Complex<T>& other, T value)
{
	Complex<T> res;
	res.re = other.re / value;
	res.im = other.im / value;

	return res;
}

template<class T>
Complex<T>& operator /= (Complex<T>& c1, T value)
{
	return c1 = c1 / value;
}

//Color operator *(Color& col, double value)
//{
//	return value * col;
//}

template<class T>
Complex<T> operator + (const Complex<T>& c1, T value)
{
	Complex<T> res;
	res.re = c1.re + value;
	res.im = c1.im + value;

	return res;
}

template<class T>
Complex<T>& operator += (Complex<T>& c1, T value)
{
	return c1 = c1 + value;
}

template<class T>
Complex<T> operator /= (Complex<T>& z, const Complex<T>& other)
{
	return z = z / other;
}

typedef Complex<double> ComplexD;