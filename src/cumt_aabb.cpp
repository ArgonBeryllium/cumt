#include "cumt_aabb.h"
#include <utility>
using namespace cumt;

std::optional<SDL_Rect> aabb::getOverlap(const SDL_Rect &a, const SDL_Rect &b)
{
	SDL_Rect out;
	if(!SDL_IntersectRect(&a, &b, &out))
		return {};
	return out;
}

inline static const std::optional<std::pair<float, float>> overlap_1d(const float& a, const float& b, const float& c, const float& d)
{
	bool bc = b<c;
	if(bc || a>d) return {};
	bool ac = a<c;
	bool bd = b<d;
	if(ac && bd)   return std::make_pair(c, b);
	if(!ac && bd)  return std::make_pair(a, b);
	if(!ac && !bd) return std::make_pair(a, d);
	if(ac && !bd)  return std::make_pair(c, d);
	std::cout << "false\n";
	return {};
}
std::optional<std::pair<v2f, v2f>> aabb::getOverlap(const Thing2D *a, const Thing2D *b)
{
	const v2f& amin = a->pos;
	const v2f& bmin = b->pos;
	const v2f amax = a->pos+a->scl;
	const v2f bmax = b->pos+b->scl;
	auto xo = overlap_1d(amin.x, amax.x, bmin.x, bmax.x);
	if(!xo) return {};
	auto yo = overlap_1d(amin.y, amax.y, bmin.y, bmax.y);
	if(!yo) return {};
	return std::make_pair(v2f{xo->first, yo->first}, v2f{xo->second-xo->first, yo->second-yo->first});
}
inline bool aabb::getOverlap(const SDL_Rect &a, const v2i &b)
{
	return b.x > a.x
		&& b.y > a.y
		&& b.x < a.x+a.w
		&& b.y < a.y+a.h;
}
inline bool aabb::getOverlap(const Thing2D *a, const v2f &b)
{
	return b.x > a->pos.x
		&& b.y > a->pos.y
		&& b.x < a->pos.x+a->scl.x
		&& b.y < a->pos.y+a->scl.y;
}

void aabb::resolveOverlaps(Thing2D *a, Thing2D *b, float aMassRatio)
{
	if(auto i = getOverlap(a, b))
	{
		const v2f pos = i->first, scl = i->second;
		if(scl.x < scl.y)
		{
			float cor = scl.x * ((pos.x-b->pos.x)!=0?1:-1);
			a->pos.x+=cor*aMassRatio;
			b->pos.x-=cor*(1-aMassRatio);
		}
		else
		{
			float cor = scl.y * ((pos.y-b->pos.y)!=0?1:-1);
			a->pos.y+=cor*aMassRatio;
			b->pos.y-=cor*(1-aMassRatio);
		}
	}
}
