#pragma once
#include <map>
#include <SDL2/SDL_mixer.h>

namespace cumt
{
struct AudioData
{
	static std::map<Mix_Chunk*, uint16_t> tracks;
	static uint16_t next_track;
};
namespace audio
{
	void init(size_t allocate_channels = 16, uint16_t rate = 44100, uint16_t format = MIX_DEFAULT_FORMAT, uint8_t channels = 2, uint16_t chunk_size = 16);
	void play(Mix_Chunk* sound, float vol = .5, int loops = 0);
}
}
