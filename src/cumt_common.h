#pragma once
#include <cstddef>
#include <sstream>
#include <iomanip>
#include <vector>
#include <functional>
#include "shitrndr/src/shitrndr.h"
#include "cumt_vec.h"

namespace cumt
{
	struct Thing;
	struct ThingSet;
}
namespace cumt::common
{
	template <typename T>
	inline T lerp(const T& a, const T& b, float f) { return a + (b-a) * f; }

	inline v2f inVec()
	{
		using namespace shitrndr;
		return v2f{float(Input::getKey(SDLK_d) || Input::getKey(SDLK_RIGHT)) - float(Input::getKey(SDLK_a) || Input::getKey(SDLK_LEFT)),
		float(Input::getKey(SDLK_s) || Input::getKey(SDLK_DOWN)) - float(Input::getKey(SDLK_w) || Input::getKey(SDLK_UP))}.normalised();
	}

	template <typename T>
	inline std::string to_string_with_precision(T value, size_t n = 3)
	{
		std::ostringstream out;
		out << std::setprecision(n) << value;
		return out.str();
	}

	inline float frand() { return float(std::rand())/float(RAND_MAX); }

	void renderFPS(v2i pos);

	void destroyIn(Thing* target, float delay);
	void act(ThingSet* ts, std::function<void()> action, float life = -1, std::function<void()> on_death = [](){});
}
