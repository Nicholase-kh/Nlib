#ifndef BOX_H
#define BOX_H

#include <vector>
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
	void moveT(const point& p); //move by touch
	void acc(const vec& a); //accelerate
	
	inline std::vector<rectangle> Box() const { return _box; }
private:
	std::vector<rectangle> _box;
	point _c;
	vec _v = 0;
};



#endif