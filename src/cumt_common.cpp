#include "cumt_common.h"
#include "cumt_render.h"
#include "cumt_things.h"
#include <cmath>
#include <cstddef>
#include <stack>
#include <algorithm>
using namespace cumt;
void common::renderFPS(v2i pos)
{
	static float lt = FD::time;
	static int f = 0, cf = 0;
	f++;
	render::text(pos, std::to_string(cf));
	if(FD::time-lt>1)
	{
		cf = f;
		f = 0;
		lt = FD::time;
	}
}

struct Killer : Thing
{
	float t;
	Thing* target;
	Killer(Thing* target_, float delay) : Thing(target_->parent_set), target(target_), t(FD::time+delay) {}
	void update() override
	{
		if(FD::time >= t)
		{
			parent_set->scheduleDestroy(target);
			parent_set->scheduleDestroy(this);
		}
	}
};
struct ActionThing : Thing
{
	std::function<void()> action, on_death;
	float life;
	bool dying;
	ActionThing(ThingSet* parent_set_, const std::function<void()>& action_, float life_ = -1, const std::function<void()> on_death_ = [](){}) :
		Thing(parent_set_), action(action_), on_death(on_death_), life(life_), dying(life_>0) {}
	void update() override
	{
		action();
		if(dying)
		{
			life -= FD::delta;
			if(life <= 0)
			{
				on_death();
				parent_set->scheduleDestroy(this);
			}
		}
	}
};
void common::destroyIn(Thing* thing, float delay)
{
	thing->parent_set->instantiate(new Killer(thing, delay));
}
void common::act(ThingSet* ts, std::function<void()> action, float life, std::function<void()> on_death)
{
	ts->instantiate(new ActionThing(ts, action, life, on_death));
}
