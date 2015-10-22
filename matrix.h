#ifndef MATRIX_H
#define MATRIX_H

#include "shape.h"

struct matrix { //二阶矩阵
	matrix(vec v, double k) //矩阵构造公式
	double a, b, c, d;
};

vec operator*(const matrix& m, const vec& v);

#endif