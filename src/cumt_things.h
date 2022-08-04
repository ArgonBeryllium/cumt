#pragma once
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include "cumt_compat.h"
#include "shitrndr/src/shitrndr.h"
#include "cumt_fd.h"
#include "cumt_vec.h"
#include "cumt_common.h"

namespace cumt
{
struct ThingSet;
struct Thing
{
	static uint64_t NEXT_ID;
	uint64_t id;
	ThingSet* parent_set;

	bool active = 1, visible = 1;
	std::string name;

	Thing(ThingSet* parent_set_ = nullptr) : parent_set(parent_set_), id(NEXT_ID++), name("Thing #"+std::to_string(id)) {}
	virtual ~Thing() {}

	virtual void start() {}
	virtual void update() {}
	virtual void render() {}
	virtual void end() {}
};
struct ThingSet
{
	std::map<uint64_t, Thing*> things_id;
	std::map<std::string, Thing*> things_name;
	std::vector<Thing*> scheduled;

	template<typename T>
	T* instantiate(T* t, const std::string& name = "")
	{
		Thing* thing = (Thing*) t;
		thing->parent_set = this;
		if(!name.empty()) thing->name = name;

		things_id[thing->id] = thing;
		things_name[thing->name] = thing;
		thing->start();
		return t;
	}

	inline Thing* get(uint64_t id) { return things_id[id]; }
	inline Thing* get(const std::string& name) { return things_name[name]; }

	void destroy(Thing* thing)
	{
		things_id.erase(thing->id);
		things_name.erase(thing->name);
		delete thing;
	}
	void destroy(uint64_t id) { destroy(things_id[id]); }
	void destroy(const std::string& name) { destroy(things_name[name]); }
	void scheduleDestroy(Thing* thing) { scheduled.push_back(thing); }
	void clear()
	{
		auto i = things_id.begin();
		while(things_id.size()!=0)
		{
			delete i->second;
			i = things_id.erase(i);
		}
		things_name.clear();
	}

	void update()
	{
		for(auto p : things_id)
			if(p.second->active) p.second->update();
		if(scheduled.size()!=0)
			for(auto i = scheduled.begin(); i < scheduled.end(); )
			{
				destroy(*i.base());
				i = scheduled.erase(i);
			}
	}
	void render()
	{
		for(auto p : things_id)
			if(p.second->visible) p.second->render();
	}
};

struct Thing2D : Thing
{
	static float unit_pix_size;
	static float view_scale;
	static v2f view_pos;

	static v2f scrToSpace(const v2i& scrPoint) { return (scrPoint-shitrndr::WindowProps::getSize()/2).to<float>()/(view_scale*unit_pix_size)+view_pos; }
	static v2i spaceToScr(const v2f& spcPoint) { return ((spcPoint-view_pos)*view_scale*unit_pix_size).to<int>()+shitrndr::WindowProps::getSize()/2; }

	static float getScalar() { return view_scale*unit_pix_size; }

	static bool onScreen(const SDL_Rect& r) { return r.x+r.w > 0 && r.y+r.h > 0 && r.x < shitrndr::WindowProps::getWidth() && r.y < shitrndr::WindowProps::getHeight(); }

	v2f pos, scl;
	Thing2D(const v2f& pos_ = {}, const v2f& scl_ = {1,1}) : Thing(), pos(pos_), scl(scl_) {}

	const v2f centre() const { return pos+scl/2; }
	const SDL_Rect getRect() const
	{
		v2i sp = spaceToScr(pos), ss = (scl*getScalar()).to<int>();
		return {sp.x, sp.y, ss.x, ss.y};
	}
	virtual void render() override
	{
		SDL_SetRenderDrawColor(shitrndr::ren, 255, 0, 0, 255);
		shitrndr::FillRect(getRect());
	}
};
struct Sprite2D : Thing2D
{
	SDL_Texture* tex;
	SDL_Rect* src;
	float angle = 0;
	v2f anchor_point = {.5, .5};
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Colour tint = {255, 255, 255, 255};
	const void setTint(const SDL_Colour& col)
	{
		tint = col;
		SDL_SetTextureColorMod(tex, tint.r, tint.g, tint.b);
		SDL_SetTextureAlphaMod(tex, tint.a);
	}

	Sprite2D(SDL_Texture* tex_, SDL_Rect* src_ = nullptr) : Thing2D(), tex(tex_), src(src_) {}

	void render() override
	{
		SDL_Rect d = getRect();
		SDL_Point centre {int(scl.x*Thing2D::view_scale*Thing2D::unit_pix_size*anchor_point.x), int(scl.y*Thing2D::view_scale*Thing2D::unit_pix_size*anchor_point.y)};
		SDL_RenderCopyEx(shitrndr::ren, tex, src, &d, angle*180./M_PI, &centre, flip);
	}
};

struct Particles2D : Thing2D
{
	size_t count;
	v2f* poss;
	float* lives;

	Particles2D(size_t count_) : count(count_), poss(new v2f[count]{{0,0}}), lives(new float[count]{1}) {}
	virtual ~Particles2D()
	{
		delete[] poss;
		delete [] lives;
	}
	void render() override { for(size_t i = 0; i != count; i++) renderParticle(i); }
	virtual void renderParticle(size_t i)
	{
		using namespace cumt;
		using namespace shitrndr;
		SetColour({255,255,255,255});
		poss[i].x = std::cos(FD::time+i);
		poss[i].y = std::sin(FD::time+i);
		v2i p = Thing2D::spaceToScr(poss[i]);
		FillRect({p.x, p.y, 10, 10});
		lives[i] -= FD::delta;
		if(lives[i]<0)
		{
			lives[i] = common::frand();
			poss[i] = v2f{1,1}*common::frand()*2 - v2f{1,1} + pos;
		}
	}
};
}
