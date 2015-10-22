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




