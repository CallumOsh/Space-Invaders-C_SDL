#ifndef aGraphicsFile
#define aGraphicsFile

#include <string>
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

using namespace std;

class Graphics
{

public:
	const int windowWidth = 1024;
	const int windowHeight = 800;
	const char* windowTitle = "Callum O'Shaughnessy - Game Programming - 16641760 - Territory Intruders";

private:
	static Graphics* instance;
	static bool isInitialised;
	SDL_Window* win;
	SDL_Renderer* ren;

public:
	static Graphics* Instance();
	static void Clean();
	static bool Initialized();
	SDL_Texture* LoadSprite(string path);
	SDL_Texture* CreateTextSprite(TTF_Font* font, string text, SDL_Color color);

	void ClearBackBuffer();
	void DrawSprite(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawLine(float startX, float startY, float endX, float endY);
	void Render();

private:
	Graphics();
	~Graphics();
	bool Init();
};
#endif