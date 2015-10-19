#ifndef _SHAPE_H
#define _SHAPE_H

#include <SDL2/SDL.h>
#include <math.h>
#include <vector>

using rectangle = SDL_Rect;
using point = SDL_Point;

struct vec {
	int dx, dy;
};

struct line {
	point vert; //vertex
	vec dir; //direction
};

struct circle {
	point c;
	int r;
	std::vector<rectangle>& shape(int pixel = 10);
};

int distance(const point& m, const point& n);

point& operator+=(point& p, const vec& v);
point operator+(const point& p, const vec& v);

int operator*(const vec& a, const vec& b);

#endif