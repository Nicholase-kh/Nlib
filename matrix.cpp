#include "matrix.h"

matrix::matrix(vec v, double k)
{
	a = 1.0 + (k - 1.0) * pow(v.dx, 2) / (v * v);
	b = (k - 1.0) * v.dx * v.dy / (v * v);
	c = b;
	d = 1.0 + (k - 1.0) * pow(v.dy, 2) / (v * v);
}

vec operator*(const matrix& m, const vec& v)
{
	vec n;
	n.dx = v.dx * m.a + v.dy * m.c;
	n.dy = v.dx * m.b + v.dy * m.d;
	return n;
}