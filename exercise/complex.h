#pragma once

#include <cmath>
#include <ostream>

class complex;

complex& _doapl(complex* ths, const complex& r);
complex& _doami(complex* ths, const complex& r);
complex& _doaml(complex* ths, const complex& r);
complex& _doamd(complex* ths, const complex& r);

class complex {
public:
	complex(double r = 0, double i = 0) : re(r), im(i) {};
	
	complex& operator += (const complex&);
	complex& operator -= (const complex&);
	complex& operator *= (const complex&);
	complex& operator /= (const complex&);

	double real() const { return re;}
	double imag() const { return im;}

private:
	double re, im;

	friend complex& _doapl(complex*, const complex&);
	friend complex& _doami(complex*, const complex&);
	friend complex& _doaml(complex*, const complex&);
	friend complex& _doamd(complex*, const complex&);

};

/// <summary>
/// 加法
/// </summary>
/// <param name="ths"></param>
/// <param name="r"></param>
/// <returns></returns>
inline complex& _doapl(complex* ths, const complex& r) {
	ths->re += r.re;
	ths->im += r.im;
	return *ths;
}

/// <summary>
/// 减法
/// </summary>
/// <param name="ths"></param>
/// <param name="r"></param>
/// <returns></returns>
inline complex& _doami(complex* ths, const complex& r) {
	ths->re -= r.re;
	ths->im -= r.im;
	return *ths;
}

/// <summary>
/// 乘法
/// </summary>
/// <param name="ths"></param>
/// <param name="r"></param>
/// <returns></returns>
inline complex& _doaml(complex* ths, const complex& r) {
	double f = ths->re * r.re - ths->im * r.im;
	ths->im = ths->re * r.im + ths->im * r.re;
	ths->re = f;
	return *ths;
}

/// <summary>
/// 除法
/// </summary>
/// <param name="ths"></param>
/// <param name="r"></param>
/// <returns></returns>
inline complex& _doamd(complex* ths, const complex& r) {
	double x = ths->re * r.re + ths->im * r.im;
	double y = ths->im * r.re - ths->re * r.im;
	double z = r.re * r.re + r.im * r.im;
	ths->re = x / z;
	ths->im = y / z;
	return *ths;
}

inline double imag(const complex& x) { return x.imag(); }
inline double real(const complex& x) { return x.real(); }

inline complex& complex::operator += (const complex& r) { return _doapl(this, r); }
inline complex& complex::operator -= (const complex& r) { return _doami(this, r); }
inline complex& complex::operator *= (const complex& r) { return _doaml(this, r); }
inline complex& complex::operator /= (const complex& r) { return _doamd(this, r); }

inline complex operator + (const complex& x, const complex& y) { return complex(real(x) + real(y), imag(x) + imag(y)); }
inline complex operator + (const complex& x, double y) { return complex(real(x) + y, imag(x)); }
inline complex operator + (double x, const complex& y) { return complex(x + real(y), imag(y)); }

inline complex operator - (const complex& x, const complex& y) { return complex(real(x) - real(y), imag(x) - imag(y));}
inline complex operator - (const complex& x, double y) { return complex(real(x) - y, imag(x)); }
inline complex operator - (double x, const complex& y) { return complex(x - real(y), imag(y)); }

inline complex operator *(const complex& x, const complex& y) { return complex(real(x) * real(y) - imag(x) * imag(y), real(x) * imag(y) + imag(x) * real(y)); }
inline complex operator *(const complex& x, double y) { return complex(real(x) * y, imag(x) * y); }
inline complex operator *(double x, const complex& y) { return complex(x * real(y), x * imag(y)); }

inline complex operator / (const complex& x, const complex& y) {
	double _x = real(x) * real(y) + imag(x) * imag(y);
	double _y = imag(x) * real(y) - real(x) * imag(y);
	double _z = real(y)*real(y) + imag(y) * imag(y);
	return complex( _x / _z, _y / _z);
}
inline complex operator / (const complex& x, double y) { return complex(real(x) / y, imag(x) / y); }
inline complex operator / (double x, const complex& y) { return complex(x, 0) / y; }

inline complex operator + (const complex& x) { return x; }
inline complex operator - (const complex& x) { return complex(-real(x), -imag(x)); }

inline bool operator == (const complex& x, const complex& y) { return real(x) == real(y) && imag(x) == imag(y); }
inline bool operator == (const complex& x, double y) { return real(x) == y && imag(x) == 0; }
inline bool operator == (double x, const complex& y) { x == real(y) && imag(y) == 0; }

inline bool operator != (const complex& x, const complex& y) { return real(x) != real(y) || imag(x) != imag(y); }
inline bool operator != (const complex& x, double y) { return real(x) != y || imag(x) != 0; }
inline bool operator != (double x, const complex& y) { return x != real(y) || 0 != imag(y); }

inline complex polar	(double r, double t) { return complex(r * cos(t), r * sin(t)); }
inline complex conj		(const complex& x) { return complex(real(x), -imag(x)); }
inline complex norm		(const complex& x) { return real(x) * real(x) + imag(x) * imag(x); }

inline std::ostream& operator << (std::ostream& os, const complex& x) { return os << "(" << real(x) << "," << imag(x) << ")"; }

