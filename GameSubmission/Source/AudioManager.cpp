#include "../Headers/AudioManager.h"

AudioManager* AudioManager::instance = NULL;

AudioManager* AudioManager::Instance()
{
	if (instance == NULL)
		instance = new AudioManager();
	return instance;
}

void AudioManager::Clean()
{
	delete instance;
	instance = NULL;
}

AudioManager::AudioManager()
{
	assetManager = AssetManager::Instance();
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		printf("Mixer Initialization Error: %s\n", Mix_GetError());
	}
}

AudioManager::~AudioManager()
{
	assetManager = NULL;
	Mix_Quit();
}

void AudioManager::PlayGameMusic(string filename, int loops)
{
	Mix_PlayMusic(assetManager->GetGameMusic(filename), loops);
}

void AudioManager::PauseGameMusic()
{
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

void AudioManager::ResumeGameMusic()
{
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}

void AudioManager::PlayGameEffects(string filename, int loops, int channel)
{
	Mix_PlayChannel(channel, assetManager->GetGameEffects(filename), loops);
}