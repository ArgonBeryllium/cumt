#include "cumt.h"
#include "shitrndr/src/shitrndr.h"
using namespace cumt;

void cumt::quickInit(int w, int h, const InitParams& ip)
{
	shitrndr::init(ip.name, w, h, 1, 0, ip.sr_renFlags);
	shitrndr::silentDefs();
	shitrndr::bg_col = ip.bg_col;
	shitrndr::WindowProps::setPixScale(ip.sr_ps);
	shitrndr::WindowProps::setLocked(ip.sr_locked);
	SDL_SetRenderDrawBlendMode(shitrndr::ren, SDL_BLENDMODE_BLEND);
}
using namespace shitrndr;
void cumt::start()
{
	if(!onLoop)
	{
		err("onLoop is unset; quitting start()");
		return;
	}
	onRender = [](double d, double t)
	{
		FrameData::delta = d;
		FrameData::time = t;
		onLoop();
	};
	if(!onKey) wrn("onKey is unset; continuing with previous onKeyDown");
	else onKeyDown = onKey;
	loop();
}

double FrameData::delta = 0, FrameData::time = 0;
