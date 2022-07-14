#include "shitrndr/src/shitrndr.h"
#include "cumt_things.h"
#include "cumt.h"

using namespace cumt;

uint64_t Thing::NEXT_ID = 0;

float Thing2D::unit_pix_size = 50;
float Thing2D::view_scale = 1;
v2f Thing2D::view_pos{};
