#pragma once
#include "cumt_compat.h"
#include <cmath>

// formulas from https://easings.net
namespace cumt::easings
{
inline float linear(float x) { return x; }

inline float easeOutElastic(float x)
{
	constexpr static float c4 = (2 * M_PI) / 3;
	return x == 0 ? 0 : x == 1 ? 1 : pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1;
}
inline float easeOutElasticSoft(float x)
{
	constexpr static float c4 = (M_PI) / 3;
	return x == 0 ? 0 : x == 1 ? 1 : pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1;
}
inline float easeInElastic(float x)
{
	return 1 - easeOutElastic(1 - x);
}
inline float easeInElasticSoft(float x)
{
	return 1 - easeOutElasticSoft(1 - x);
}
inline float easeInOutElastic(float x)
{
	constexpr static float c5 = (2 * M_PI) / 4.5;

	return x == 0 ? 0 : x == 1 ? 1
	: x < 0.5
	? -(pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2
	: (pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1;
}

inline float easeOutBounce(float x)
{
	constexpr static float n1 = 7.5625;
	constexpr static float d1 = 2.75;

	if (x < 1 / d1) return n1 * x * x;
	else if (x < 2 / d1)
	{
		x -= 1.5 / d1;
    	return n1 * x * x + 0.75;
	}
	else if (x < 2.5 / d1)
	{
		x -= 2.25 / d1;
		return n1 * x * x + 0.9375;
	}
	else 
	{
		x -= 2.625 / d1;
    	return n1 * x * x + 0.984375;
	}
}
inline float easeInBounce(float x) { return 1 - easeOutBounce(1 - x); }
inline float easeInOutBounce(float x)
{
	return x < 0.5
		? (1 - easeOutBounce(1 - 2 * x)) / 2
		: (1 + easeOutBounce(2 * x - 1)) / 2;
}
};
