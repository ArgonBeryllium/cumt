#include "shitrndr/src/shitrndr.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "cumt.h"
using namespace shitrndr;
using namespace cumt;

ThingSet set;

Animation<v2f>* anim;
void gameStart()
{
	RenderData::loadFont("res/unifont.ttf", 12);
	WindowProps::setLockType(WindowProps::CUTOFF);

	Thing2D::view_scale = .5;
	set.instantiate(new Thing2D());

	std::map<float, Keyframe<v2f>> frames;
	frames[0.f] = {v2f()};
	frames[1.f] = {v2f(2, 0)};
	frames[2.f] = {v2f(-2, 0), easings::easeInOutElastic};
	frames[3.f] = {v2f(0, -4), easings::easeOutElasticSoft};
	frames[4.f] = {v2f(), easings::easeOutBounce};
	anim = new Animation<v2f>(&((Thing2D*)set.get(0))->pos, frames);
	anim->loop = 1;
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
void renderEasing(v2i pos, float(*easing)(float), float cutoff = 1, SDL_Colour col = {255,255,255,255})
{
	v2i pp = pos;
	for(float i = 0; i != 50; i++)
	{
		if(i/50 < cutoff) SetColour(col);
		else SetColour({});
		v2i cp = {pos.x+(int)i, pos.y+int(easing(i/50)*50)};
		SDL_RenderDrawLine(ren, pp.x, pp.y, cp.x, cp.y);
		pp = cp;
	}
}
void gameLoop()
{
	set.update();
	anim->pace = 2;
	anim->update();

	render::pattern::checkerBoard(0,0,30);
	set.render();

	size_t id = anim->getCurrentID();
	float pt = anim->getPair(id-1).first;
	std::pair<float, Keyframe<v2f>> ck = anim->getPair(id);

	renderEasing({10, 30}, ck.second.easing, (anim->time-pt)/(ck.first-pt));
	common::renderFPS({});
	render::text({0,16},common::to_string_with_precision(FD::delta,10));

	//int w = WindowProps::getWidth(), h = WindowProps::getHeight();
	//render::text_cached({1*w/4, h/3}, "abc", {.col = {000,255,255}});
	//render::text_cached({2*w/4, h/3}, "abc", {.col = {255,000,255}});
	//render::text_cached({3*w/4, h/3}, "abc", {.col = {255,255,000}});
	//render::text_cached({1*w/4, h/2}, "abcdef@", {.col = {000,255,255}});
	//render::text_cached({2*w/4, h/2}, "abcdef@", {.col = {255,000,255}});
	//render::text_cached({3*w/4, h/2}, "abcdef@", {.col = {255,255,000}});
}

int CUMT_MULP_MAIN()
{
	quickInit(540, 540);
	gameStart();
	cumt::onLoop = &gameLoop;
	cumt::onKey = &gameKeyDown;
	start();
}
