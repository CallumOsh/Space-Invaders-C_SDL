#ifndef aAssetManager
#define aAssetManager

#include <map>
#include "SDL_mixer.h"
#include "Graphics.h"

using namespace std;

class AssetManager
{

private:
	static AssetManager* instance;

	map<string, SDL_Texture*> mSprites;
	map<string, SDL_Texture*> mText;
	map<string, TTF_Font*> mFonts;
	map<string, Mix_Music*> mMusic;
	map<string, Mix_Chunk*> mSFX;

public:
	static AssetManager* Instance();
	static void Clean();

	SDL_Texture* GetSprite(string filename);
	SDL_Texture* GetScreenText(string text, string filename, int size, SDL_Color color);
	Mix_Music* GetGameMusic(string filename);
	Mix_Chunk* GetGameEffects(string filename);

private:
	AssetManager();
	~AssetManager();
	TTF_Font* GetGameFont(string filename, int size);
};
#endif