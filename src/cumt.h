#pragma once
#include <math.h>
#include <inttypes.h>
#include <map>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include "shitrndr/src/shitrndr.h"

#include "cumt_logging.h"
#include "cumt_fd.h"
#include "cumt_vec.h"
#include "cumt_common.h"
#include "cumt_render.h"
#include "cumt_things.h"
#include "cumt_audio.h"
#include "cumt_animation.h"
#include "cumt_easings.h"
#include "cumt_aabb.h"

#if defined _WIN32 || defined __CYGWIN__
#define CUMT_MULP_MAIN WinMain
#else
#define CUMT_MULP_MAIN main
#endif

namespace cumt
{
struct InitParams
{
	const char* name = "CUMT window";
	SDL_Colour bg_col;

	int sr_ps = 2;
	int sr_renFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	bool sr_locked = 1;
};
void quickInit(int w = 960, int h = 540, const InitParams& ip = {});
void start();
inline void (*onLoop)();
inline void (*onKey)(const SDL_Keycode& key);
}
