#include <cstddef>
#include <unordered_map>
#include <string>
#include <utility>
#include <SDL2/SDL_image.h>

#include "cumt_compat.h"
#include "shitrndr/src/shitrndr.h"
#include "cumt_render.h"

using namespace cumt;
using namespace shitrndr;

std::vector<TTF_Font*> RenderData::fonts;
void render::line(v2f a, v2f b) { line(Thing2D::spaceToScr(a), Thing2D::spaceToScr(b)); }
void render::line(v2i a, v2i b) { SDL_RenderDrawLine(ren, a.x, a.y, b.x, b.y); }
void render::dottedLine(v2f a, v2f b, const uint32_t segl) { dottedLine(Thing2D::spaceToScr(a), Thing2D::spaceToScr(b), segl); }
void render::dottedLine(v2i a, v2i b, const uint32_t segl)
{
	int l = (a-b).getLength();
	v2f n = (b.to<float>()-a.to<float>()).normalised();
	for(int i = 0; i<l; i+=2*segl) SDL_RenderDrawPoint(ren, int(a.x+n.x*i), int(a.y+n.y*i));
}
void render::vector(v2f origin, v2f v) { line(origin, origin+v); }

const v2f render::TextData::LEFT = {0, 0};
const v2f render::TextData::CENTRE = {.5, 0};
const v2f render::TextData::RIGHT = {1, 0};

void render::texture_with_td(SDL_Texture* t, v2i pos, const TextData& td)
{
	int w, h;
	SDL_QueryTexture(t, 0, 0, &w, &h);
	v2f siz = v2f{(float)w, (float)h}*td.scale;
	pos -= siz*td.anchor;
	SDL_Rect r = {pos.x, pos.y, int(siz.x), int(siz.y)};
	SDL_Point c = {int(siz.x*td.anchor.x), int(siz.y*td.anchor.y)};
	SDL_RenderCopyEx(ren, t, 0, &r, td.angle*180./M_PI, &c, SDL_FLIP_NONE);
}
SDL_Texture* render::text(v2i pos, const char* text, const TextData& td)
{
	SDL_Surface* s = TTF_RenderUTF8_Solid(RenderData::fonts[td.font_id], text, td.col);

	SDL_Texture* t = SDL_CreateTextureFromSurface(ren, s);
	if(td.render) render::texture_with_td(t, pos, td);
	SDL_FreeSurface(s);
	if(td.destroy) SDL_DestroyTexture(t);
	return t;
}
SDL_Texture* render::text(v2i pos, const std::string &text, const TextData &td) { return render::text(pos, text.c_str(), td); }

/*
struct TextCacheKey
{
	char c;
	SDL_Colour col;
	size_t font_id;
};
static inline uint16_t acol2num(const SDL_Colour& col) { return col.a<<24 | col.r<<16 | col.g<<8 | col.b; };
static inline bool operator<(const TextCacheKey& a, const TextCacheKey& b)
{
	return a.c<b.c || acol2num(a.col)<acol2num(b.col) || a.font_id<b.font_id;
}
static std::map<TextCacheKey, SDL_Texture*> text_cache;
void render::text_cached(v2i pos, const char* text, const TextData& td) { return render::text_cached(pos, std::string(text), td); }
void render::text_cached(v2i pos, const std::string &text, TextData td)
{
	for(char c : text)
	{
		SDL_Texture* t = text_cache[TextCacheKey{c, td.col, td.font_id}];
		if(!t)
		{
			bool tdd = td.destroy, tdr = td.render;
			td.destroy = false;
			td.render = false;
			t = render::text(pos, text, td);
			td.destroy = tdd;
			td.render = tdr;
			std::hex(std::cout);
			std::cout << "creating new text²ure: " << text << acol2num(td.col) << '\n';
			text_cache[{c, td.col, td.font_id}] = t;
		}
		render::texture_with_td(t, pos, td);
	}
}
void render::text_cache_clear()
{
	text_cache.clear();
}
bool render::text_cache_remove(char c, const TextData& td)
{
	SDL_Texture* t = text_cache[{c, td.col, td.font_id}];
	if(!t) return false;
	SDL_DestroyTexture(t);
	return true;
}
*/

void render::pattern::grid(int x, int y, int s)
{
	int w = WindowProps::getWidth(), h = WindowProps::getHeight();
	if(s<=0)
	{
		FillRect({0,0,w,h});
		return;
	}
	x%=s;
	y%=s;
	w+=s;
	h+=s;
	for(int ey = 0; ey < h; ey+=s)
	{
		int py = (ey+y);
		line(v2i{0,py}, v2i{w,py});
	}
	for(int ex = 0; ex < w; ex+=s)
	{
		int px = (ex+x);
		line(v2i{px,0}, v2i{px,w});
	}
}
void render::pattern::dottedGrid(int x, int y, int s, int segl)
{
	int w = WindowProps::getWidth(), h = WindowProps::getHeight();
	if(s<=0)
	{
		FillRect({0,0,w,h});
		return;
	}
	x%=s;
	y%=s;
	w+=s;
	h+=s;
	for(int ey = 0; ey < h; ey+=s)
	{
		int py = (ey+y);
		dottedLine(v2i{0,py}, v2i{w,py}, segl);
	}
	for(int ex = 0; ex < w; ex+=s)
	{
		int px = (ex+x);
		dottedLine(v2i{px,0}, v2i{px,w}, segl);
	}
}

void render::pattern::checkerBoard(int x, int y, int s, SDL_Color c1, SDL_Color c2)
{
	int w = WindowProps::getWidth(), h = WindowProps::getHeight();
	if(s<=0) return;
	int mx = x%s;
	int my = y%s;
	w/=s;
	h/=s;
	w++;
	h++;
	for(int ex = -1; ex < w; ex++)
		for(int ey = -1; ey < h; ey++)
		{
			if((ex+ey-x/s-y/s)%2) SDL_SetRenderDrawColor(ren, c1.r, c1.g, c1.b, c1.a);
			else SDL_SetRenderDrawColor(ren, c2.r, c2.g, c2.b, c2.a);
			FillRect({ex*s+mx, ey*s+my, s, s});
		}
}

void render::pattern::noise(int x, int y, float bias, int seed, int s)
{
	if(s <= 0) return;
	int w = WindowProps::getWidth(), h = WindowProps::getHeight();
	bias *= float(RAND_MAX);
	while(x<0) x += w;
	while(y<0) y += h;
	std::srand(seed);
	if(s==1)
	{
		for(int ix = 0; ix != w; ix++)
			for(int iy = 0; iy != h; iy++)
				if(std::rand()<bias) SDL_RenderDrawPoint(ren, (ix+x)%w, (iy+y)%h);
	} else
		for(int ix = 0; ix < w; ix+=s)
			for(int iy = 0; iy < h; iy+=s)
				if(std::rand()<bias) FillRect({(ix+x)%w, (iy+y)%h, s, s});
}

static SDL_Texture* effects_proxy;
void render::effect::init()
{
#if defined _WIN32 || defined __CYGWIN__ || defined __EMSCRIPTEN__
	effects_proxy = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WindowProps::getWidth(), WindowProps::getHeight());
#else
	effects_proxy = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WindowProps::getWidth(), WindowProps::getHeight());
#endif
}
void render::effect::aberrate(v2i r, v2i g, v2i b, SDL_Texture* source, SDL_Texture* target, SDL_Rect rect)
{
	SDL_SetRenderTarget(ren, effects_proxy);

	SDL_SetRenderDrawColor(ren, 0,0,0, 255);
	SDL_RenderClear(ren);

	SDL_SetTextureBlendMode(source, SDL_BLENDMODE_ADD);

	SDL_SetTextureColorMod(source, 255, 0, 0);
	rect.x = r.x;
	rect.y = r.y;
	Copy(WindowProps::_renProxy, rect);

	SDL_SetTextureColorMod(source, 0, 255, 0);
	rect.x = g.x;
	rect.y = g.y;
	Copy(WindowProps::_renProxy, rect);

	SDL_SetTextureColorMod(source, 0, 0, 255);
	rect.x = b.x;
	rect.y = b.y;
	Copy(WindowProps::_renProxy, rect);

	SDL_SetTextureColorMod(source, 255, 255, 255);
	SDL_SetTextureBlendMode(source, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(ren, target);

	rect.x = 0;
	rect.y = 0;
	Copy(effects_proxy, rect);
}
