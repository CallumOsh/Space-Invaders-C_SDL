#ifndef aAudioManagerFile
#define aAudioManagerFile

#include "AssetManager.h"

using namespace std;

class AudioManager 
{

public:
	static AudioManager* Instance();
	static void Clean();
	void PlayGameMusic(string filename, int loops = -1);
	void PauseGameMusic();
	void ResumeGameMusic();
	void PlayGameEffects(string filename, int loops = 0, int channel = 0);

private:
	AudioManager();
	~AudioManager();
	static AudioManager* instance;
	AssetManager* assetManager;
};
#endif
