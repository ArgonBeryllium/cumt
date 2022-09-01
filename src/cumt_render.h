#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "cumt_logging.h"
#include "cumt_vec.h"
#include "cumt_common.h"
#include "cumt_things.h"

namespace cumt
{
struct RenderData
{
	static std::vector<TTF_Font*> fonts;
	static void initTTF()
	{
		if(TTF_Init())
			err("Failed to initialise SDL_TTF: ", TTF_GetError());
	}
	static void loadFont(const char* path, const uint16_t ps)
	{
		if(!TTF_WasInit())
		{
			wrn("Attempting to loadFont prior to calling initTTF; Calling initTTF and continuing");
			initTTF();
		}
		TTF_Font* font = TTF_OpenFont(path, ps);
		if(!font)
		{
			err("Failed to load font '", path, "': ", TTF_GetError());
			return;
		}
		else fonts.push_back(font);
	}
};
namespace render
{
void line(v2f a, v2f b);
void line(v2i a, v2i b);
void dottedLine(v2f a, v2f b, const uint32_t segl = 3);
void dottedLine(v2i a, v2i b, const uint32_t segl = 3);
void vector(v2f origin, v2f v);

struct TextData
{
	size_t font_id = 0;

	static const v2f LEFT, CENTRE, RIGHT;
	v2f anchor = LEFT;
	v2f scale = {1,1};
	float angle = 0;

	SDL_Colour col = {255,255,255,255};
	bool render = 1; // ignored by texture_with_td
	bool destroy = 1;
};

SDL_Texture* text(v2i pos, const char* text, const TextData& td = {});
SDL_Texture* text(v2i pos, const std::string& text, const TextData& td = {});
//void text_cached(v2i pos, const std::string& text, TextData td = {});
//void text_cached(v2i pos, const char* text, const TextData& td = {});
//void text_cache_clear();
//bool text_cache_remove(char c, const TextData& td = {});
void texture_with_td(SDL_Texture* t, v2i pos, const TextData& td);

namespace pattern
{
void grid(int x, int y, int s);
void dottedGrid(int x, int y, int s, int segl = 1);
void checkerBoard(int x, int y, int s, SDL_Colour c1 = {35,35,35,255}, SDL_Colour c2 = {0,0,0,255});
void noise(int x, int y, float bias, int seed = 5, int s = 1);
}
namespace effect
{
void init();
void aberrate(v2i r = {-1,0}, v2i g = {0,0}, v2i b = {1,0}, SDL_Texture* source = shitrndr::WindowProps::_renProxy, SDL_Texture* target = shitrndr::WindowProps::_renProxy, SDL_Rect rect = shitrndr::WindowProps::getSizeRect());
};
}
}
