#pragma once
#include <map>
#include "cumt_logging.h"
#include "cumt_common.h"
#include "cumt_fd.h"
#include "cumt_easings.h"

namespace cumt
{
template <typename T>
struct Keyframe
{
	T state;
	float (*easing)(float t) = easings::linear;
	void apply(T* prop, const T& prev, float f) { *prop = common::lerp(prev, state, easing(f)); }
};
template <typename T>
struct Animation
{
	T* prop;
	std::map<float, Keyframe<T>> keyframes;
	bool playing = true, loop = false;
	float time = 0, pace = 1, duration;

	Animation(T* prop_, std::map<float, Keyframe<T>> keyframes_) : prop(prop_), keyframes(keyframes_)
	{
		duration = std::prev(keyframes.end())->first;
	}

	void play() { playing = 1; }
	void pause() { playing = 0; }
	void stop()
	{
		playing = 0;
		time = 0;
	}
	bool done() { return time >= duration; }

	size_t getCurrentID()
	{
		size_t i = 0;
		for(std::pair<float, Keyframe<T>> p : keyframes)
		{
			if(p.first>time) return i;
			i++;
		}
		return 0;
	}
	std::pair<float, Keyframe<T>> getPair(size_t id)
	{
		size_t i = 0;
		for(std::pair<float, Keyframe<T>> p : keyframes)
		{
			if(i==id) return p;
			i++;
		}
		err("error: no matching keyframe pair. Property:", prop);
		return {};
	}

	void update()
	{
		if(!playing) return;
		time += FD::delta*pace;
		if(time>=duration)
		{
			if(loop) time = 0;
			else
			{
				playing = 0;
				return;
			}
		}

		std::pair<float, T> prev = {0.f,*prop};
		for(std::pair<float, Keyframe<T>> p : keyframes)
		{
			if(p.first>time)
			{
				p.second.apply(prop, prev.second, (time-prev.first)/(p.first-prev.first));
				break;
			}
			else prev = {p.first, p.second.state};
		}
	}
};
}
