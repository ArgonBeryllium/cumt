#pragma once
#include <functional>
#include <math.h>
#include <inttypes.h>
#include <map>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include "shitrndr/src/shitrndr.h"

#include "cumt_compat.h"
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
inline std::function<void()> onLoop;
inline std::function<void(const SDL_Keycode& key)> onKey;
}
