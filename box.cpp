#include "box.h"

box::box(const std::vector<rectangle>& box): _box(box)
{
	if (!box.empty()) {
		rectangle rect = box[0];
		_c = {rect.x, rect.y};
		for (int i = 0; i != box.size(); ++i)
		{
			if (rect.x >= box[i].x)
				rect.x = box[i].x;
			if (rect.y >= box[i].y)
				rect.y = box[i].y;
			if (rect.x + rect.w <= box[i].x + box[i].w)
				rect.w = box[i].x + box[i].w - rect.x;
			if (rect.y + rect.h <= box[i].y + box[i].h)
				rect.h = box[i].y + box[i].h - rect.y;
		}
		_box.push_front(rect);
	}else {
		_c = {0, 0};
	}
}

box::box(const vec& v, const std::vector<rectangle>& box): _v(v), _box(box)
{
	if (!box.empty()) {
		rectangle rect = box[0];
		_c = {rect.x, rect.y};
		for (int i = 0; i != box.size(); ++i)
		{
			if (rect.x >= box[i].x)
				rect.x = box[i].x;
			if (rect.y >= box[i].y)
				rect.y = box[i].y;
			if (rect.x + rect.w <= box[i].x + box[i].w)
				rect.w = box[i].x + box[i].w - rect.x;
			if (rect.y + rect.h <= box[i].y + box[i].h)
				rect.h = box[i].y + box[i].h - rect.y;
		}
		_box.push_front(rect);
	}else {
		_c = {0, 0};
	}
}

void box::move()
{
	for (auto& rect : _box)
	{
		_box.x += _v.dx;
		_box.y += _v.dy;
	}
	mov_box(_v);
}

void box::moveT(const vec& t)
{
	for (auto& rect : _box)
	{
		_box.x += t.dx;
		_box.y += t.dy;
	}
	mov_box(t);
	_v = { 0, 0 };
}

void box::acc(const vec& a)
{
	_v += a;
}

void reflect(const vec& l)
{
	matrix mirr(l, -1); //matrix mirror
	this->_v = mirr * this->_v;
}

bool box::InBox(const point& p)
{
	if (!_box.empty())
	{
		for (auto rect : _box)
		{
			if (p.x - rect.x <= rect.w)
				if(p.y - rect.y <= rect.h)
					return true;
		}
		return false;
	}else {
		return p == _c;
	}
}

std::vector<rectangle>&& box::Box() const
{
	auto box = _box;
	if (!box.empty())
		box.pop_front();
	return std::move(box);
}

box&& reflect(box dot, const line& l)
{
	dot = dot.reflect(l);
	return std::move(dot);
}

bool overlap(const std::vector<rectangle>& boxA, const std::vector<rectangle>& boxB)
{
	if (!(boxA[0].x > boxB[0].x+boxB[0].w ||
		  boxB[0].x > boxA[0].x+boxA[0].w || 
		  boxA[0].y > boxB[0].y+boxB[0].h ||
		  boxB[0].y > boxA[0].y+boxA[0].h ))
	{
		int leftA, rightA, topA, bottomA;
		int letfB, rightB, topB, bottomB;
		int i, j;
		for (i = 1; i != boxA.size(); ++i)
		{
			leftA = boxA[i].x;
			rightA = leftA + boxA[i].w;
			topA = boxA.y;
			bottomA = topA[i] + boxA[i].h;
			for (j = 1; j != boxB.size(); ++j)
			{
				leftB = boxB[j].x;
				rightB = leftB + boxB[j].w;
				topB = boxB[j].y;
				bottomB = topB + boxB[j].h;
				if (!(leftA > rightB ||
					  leftB > rightA ||
					  topA > bottomB ||
					  topB > bottomA ))
				{
					return true;
				}
			}
		}
	}
	return false;
}