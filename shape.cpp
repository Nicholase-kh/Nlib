#include "shape.h"

std::vector<rectangle>& circle::shape(int pixel)
{
	std::vector<rectangle> shape;
	rectangle rect;
	if (int(2*r / pixel) == 0)
	{
		rect = {c.x - r/sqrt(2), c.y - r/sqrt(2), 2*r/sqrt(2), 2*r/sqrt(2)};
		shape.push_back(rect);
	}
	else {
		int w = 2*r - pixel/2, h, left, right;
		rect = {c.x - r + pixel/2, 0, pixel, 0};
		relt = sqrt(pow(r, 2) - pow(w - r, 2));
		while (int(w / pixel) != 0)
		{
			w -= pixel;
			right = sqrt(pow(r, 2) - pow(w - r, 2));
			rect.h = left < right ? 2*letf : 2*right;
			rect.y = c.y - rect.h/2;
			shape.push_back(rect);
			rect.x += pixel;
			left = right;
		}
		if (w % pixel != 0)
		{
			rect.w = w % pixel;
			right = sqrt(pow(r, 2) - pow(w - r, 2));
			rect.h = left < right ? 2*letf : 2*right;
			rect.y = c.y - rect.h/2;
			shape.push_back(rect);
		}
	}
	return shape;
}

int distance(const point& m, const point& n)
{
	return sqrt(pow(m.x - n.x, 2) + pow(m.y - n.y, 2));
}

point& operator+=(point& p, const vec& v)
{
	point poi;
	return poi = p + v;
}

point operator+(const point& p, const vec& v)
{
	point poi;
	poi = p.x + v.dx;
	poi = p.y + v.dy;
	return poi;
}

int operator*(const vec& a, const vec& b)
{
	return a.dx * b.dx + a.dy * b.dy;
}