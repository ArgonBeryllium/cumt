#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "cumt_logging.h"
#include "cumt_audio.h"

using namespace cumt;

std::map<Mix_Chunk*, uint16_t> AudioData::tracks = {};
uint16_t AudioData::next_track = 0;
void audio::init(size_t allocate_channels, uint16_t rate, uint16_t format, uint8_t channels, uint16_t chunk_size)
{
	if(Mix_OpenAudio(rate, format, channels, chunk_size)<0) err("Failed to initialise SDL_mixer: ", Mix_GetError());
	else Mix_AllocateChannels(allocate_channels);
}
void audio::play(Mix_Chunk *sound, float vol, int loops)
{
	if(!AudioData::tracks[sound]) AudioData::tracks[sound] = AudioData::next_track++;
	Mix_Volume(AudioData::tracks[sound], std::max(std::min(vol, 1.0f), 0.0f)*(float)MIX_MAX_VOLUME);
	Mix_PlayChannel(AudioData::tracks[sound], sound, loops);
}
