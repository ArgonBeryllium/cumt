#include "cumt_common.h"
#include "cumt_render.h"
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
