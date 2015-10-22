#ifndef BOX_H
#define BOX_H

#include <vector>
#include <utility>
#include <SDL2/SDL.h>

#include "shape.h"
#include "matrix.h"

class box {
public:
	box(const point& p): _c(p) { }
	box(const point& c, const vec& v): _c(c), _v(v) { }
	box(const std::vector<rectangle>& box);
	box(const vec& v, const std::vector<rectangle>& box);
	
	void move();
	void moveT(const vec& t); //move by touch
	void acc(const vec& a); //accelerate
	bool InBox(const point& p);
	std::vector<rectangle>&& Box() const;
private:
	inline void mov_box(const vec& v) { _c += v; }
	std::vector<rectangle> _box;
	point _c;
	vec _v = 0;
};

box mirror(const box& dot, const line& l);

bool overlap(const std::vector<rectangle>& boxA, const std::vector<rectangle>& boxB);
#endif