#pragma once
#include "SDL_mixer.h"
#include <vector>

using sound_id = unsigned int;
class Sound_System
{
public:
	virtual ~Sound_System() = default;
	virtual void Play(const sound_id id, const float volume) = 0;
	virtual void AddAudioclip(const char* file) = 0;
};

class SDL_Sound_System : public Sound_System
{
public:
	void Play(const sound_id id, const float volume) override;
	void AddAudioclip(const char* file);
	//void RemoveAudioclip(int index);
	~SDL_Sound_System() override;

private:
	std::vector<Mix_Chunk*> m_pAudioclips;
};

class Null_Sound_System : public Sound_System
{
	void Play(const sound_id, const float) override {};
	void AddAudioclip(const char*) override {};
};



