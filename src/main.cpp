#include "cumt_aabb.h"
#include "cumt_render.h"
#include "cumt_things.h"
#include "shitrndr/src/shitrndr.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "cumt.h"
using namespace shitrndr;
using namespace cumt;

ThingSet set;
Thing2D* a, *b;

void gameStart()
{
	RenderData::loadFont("res/unifont.ttf", 12);
	WindowProps::setLockType(WindowProps::CUTOFF);

	Thing2D::view_scale = .5;
	a = set.instantiate(new Thing2D());
	b = set.instantiate(new Thing2D({}, {3, 2}));
}
void gameKeyDown(const SDL_Keycode& key)
{
	switch(key)
	{
		case SDLK_q:
			SDL_Quit();
			std::exit(0);
			break;
	}
}
void gameLoop()
{
	set.update();

	render::pattern::checkerBoard(0,0,30);
	set.render();

	a->pos = Thing2D::scrToSpace(Input::getMP());
	auto in = aabb::getOverlap(a->getRect(), b->getRect());
	auto in2 = aabb::getOverlap(a, b);
	if(in2)
	{
		SetColour({255,0,255,255});
		if(in) FillRect(*in);
		SetColour({255,255,0,255});
		v2i pos = Thing2D::spaceToScr(in2->first);
		v2i siz = in2->second*Thing2D::getScalar();
		FillRect({pos.x, pos.y, siz.x, siz.y});
	}
	aabb::resolveOverlaps(a, b);
}

int CUMT_MULP_MAIN()
{
	quickInit(540, 540);
	gameStart();
	cumt::onLoop = &gameLoop;
	cumt::onKey = &gameKeyDown;
	start();
}
