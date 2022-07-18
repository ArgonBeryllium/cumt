#pragma once
#include "cumt_things.h"
#include <optional>

namespace cumt::aabb
{
SDL_Rect* getOverlap(const SDL_Rect& a, const SDL_Rect& b);
std::optional<std::pair<v2f, v2f>> getOverlap(const Thing2D* a, const Thing2D* b);
bool getOverlap(const SDL_Rect& a, const v2i& b);
bool getOverlap(const Thing2D* a, const v2f& ss_b);
void resolveOverlaps(Thing2D* a, Thing2D* b, float aMassRatio = .5f);
}
