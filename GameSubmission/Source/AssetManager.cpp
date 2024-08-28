#include "../Headers/AssetManager.h"

AssetManager* AssetManager::instance = NULL;

AssetManager* AssetManager::Instance() 
{
	if (instance == NULL)
		instance = new AssetManager();
	return instance;
}

void AssetManager::Clean() 
{
	delete instance;
	instance = NULL;
}

AssetManager::AssetManager() 
{
}

AssetManager::~AssetManager()
{
	for (auto tex : mSprites)
	{
		if (tex.second != NULL)
		{
			SDL_DestroyTexture(tex.second);
		}
	}
	mSprites.clear();

	for (auto text : mText) 
	{
		if (text.second != NULL) 
		{
			SDL_DestroyTexture(text.second);
		}
	}
	mText.clear();

	for (auto font : mFonts) 
	{
		if (font.second != NULL) 
		{
			TTF_CloseFont(font.second);
		}
	}
	mFonts.clear();

	for (auto music : mMusic)
	{
		if (music.second != NULL)
		{
			Mix_FreeMusic(music.second);
		}
	}
	mMusic.clear();

	for (auto sfx : mSFX)
	{
		if (sfx.second != NULL)
		{
			Mix_FreeChunk(sfx.second);
		}
	}
	mSFX.clear();
}

SDL_Texture* AssetManager::GetSprite(string filename)
{
	string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	if (mSprites[fullPath] == nullptr)
		mSprites[fullPath] = Graphics::Instance()->LoadSprite(fullPath);
	return mSprites[fullPath];
}

TTF_Font* AssetManager::GetGameFont(string filename, int size)
{
	string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	string key = fullPath + (char)size;

	if (mFonts[key] == nullptr)
	{
		mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);
		if (mFonts[key] == nullptr)
			printf("Font Loading Error: Font-%s Error-%s", filename.c_str(), TTF_GetError());
	}
	return mFonts[key];
}

SDL_Texture* AssetManager::GetScreenText(string text, string filename, int size, SDL_Color color)
{
	TTF_Font* font = GetGameFont(filename, size);
	string key = text + filename + (char)size + (char)color.r + (char)color.b + (char)color.g;

	if (mText[key] == nullptr)
		mText[key] = Graphics::Instance()->CreateTextSprite(font, text, color);
	return mText[key];
}

Mix_Music* AssetManager::GetGameMusic(string filename) 
{
	string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	if (mMusic[fullPath] == nullptr) 
	{
		mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());
		if (mMusic[fullPath] == NULL)
			printf("Music Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
	}
	return mMusic[fullPath];
}

Mix_Chunk* AssetManager::GetGameEffects(string filename)
{
	string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	if (mSFX[fullPath] == nullptr) 
	{
		mSFX[fullPath] = Mix_LoadWAV(fullPath.c_str());
		if (mSFX[fullPath] == NULL)
			printf("SFX Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
	}
	return mSFX[fullPath];
}