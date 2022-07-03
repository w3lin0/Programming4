#include "MiniginPCH.h"
#include "Sound_System.h"

void SDL_Sound_System::Play(const sound_id id, const float volume)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024) == -1) {
		std::cout << "Open audio failed!\n";
	}
	Mix_VolumeChunk(m_pAudioclips.at(id), (int)volume);
	Mix_PlayChannel(-1, m_pAudioclips.at(id), 0);
}

void SDL_Sound_System::AddAudioclip(const char* file)
{
	m_pAudioclips.push_back(Mix_LoadWAV(file));
}

SDL_Sound_System::~SDL_Sound_System()
{
	for (auto audioclip : m_pAudioclips) {
		delete audioclip;
		audioclip = nullptr;
	}
	Mix_CloseAudio();
}
