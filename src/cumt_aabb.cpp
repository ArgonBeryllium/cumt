#include "cumt_aabb.h"
using namespace cumt;

SDL_Rect* aabb::getOverlap(const SDL_Rect &a, const SDL_Rect &b)
{
	SDL_Rect* out = new SDL_Rect();
	if(!SDL_IntersectRect(&a, &b, out))
	{
		delete out;
		return 0;
	}
	return out;
}
SDL_Rect* aabb::getOverlap(const Thing2D *a, const Thing2D *b) { return getOverlap(a->getRect(), b->getRect()); }
bool aabb::getOverlap(const SDL_Rect &a, const v2i &b) { return b.x > a.x && b.y > a.y && b.x < a.x+a.w && b.y < a.y+a.h; }
bool aabb::getOverlap(const Thing2D *a, const v2f &b) { return getOverlap(a->getRect(), Thing2D::spaceToScr(b)); }

void aabb::resolveOverlaps(Thing2D *a, Thing2D *b, float aMassRatio)
{
	if(SDL_Rect* i = getOverlap(a, b))
	{
		if(i->w<i->h)
		{
			float cor = i->w / Thing2D::getScalar() * ((i->x-Thing2D::spaceToScr(b->pos).x)!=0?1:-1);
			a->pos.x+=cor*aMassRatio;
			b->pos.x-=cor*(1-aMassRatio);
		}
		else
		{
			float cor = i->h / Thing2D::getScalar() * ((i->y-Thing2D::spaceToScr(b->pos).y)!=0?1:-1);
			a->pos.y+=cor*aMassRatio;
			b->pos.y-=cor*(1-aMassRatio);
		}
		delete i;
	}
}
