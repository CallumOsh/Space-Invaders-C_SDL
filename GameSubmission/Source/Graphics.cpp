#include "../Headers/Graphics.h"

Graphics* Graphics::instance = NULL;
bool Graphics::isInitialised = false;

Graphics* Graphics::Instance() 
{
	if (instance == NULL)
		instance = new Graphics();
	return instance;
}

void Graphics::Clean()
{
	delete instance;
	instance = NULL;
	isInitialised = false;
}

bool Graphics::Initialized()
{
	return isInitialised;
}

Graphics::Graphics()
{
	isInitialised = Init();
}

Graphics::~Graphics() 
{
	SDL_DestroyWindow(win);
	win = NULL;

	SDL_DestroyRenderer(ren);
	ren = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Graphics::Init() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[SDL Initialization Error: %s]\n", SDL_GetError());
		return false;
	}
	else 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[SDL Initialisation Success]");
	}

	win = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (win == NULL) 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[Window Creation Error: %s]\n", SDL_GetError());
		return false;
	}
	else 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[Window Created]");
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL) 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[Render Creation Error: %s]\n", SDL_GetError());
		return false;
	}
	else 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[Renderer Created]");
	}
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[Draw Colour Set to Black]");

	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags)) 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[Image Initialisation Error: %s]\n", IMG_GetError());
		return false;
	}
	else 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[Image Initialisation Success]");
	}

	if (TTF_Init() == -1) 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[TTF Font Initialisation Error: %s]\n", TTF_GetError());
		return false;
	}
	else 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[TTF Font Initialisation Success]");
	}
	return true;
}

SDL_Texture* Graphics::LoadSprite(string path)
{
	SDL_Texture* tex = NULL;

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL) 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[Image Load Error: Path(%s) - Error(%s)]\n", path.c_str(), IMG_GetError());
		return tex;
	}
	else 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[Image Load Success]");
	}

	tex = SDL_CreateTextureFromSurface(ren, surface);
	if (tex == NULL) 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[Sprite Creation Error: %s]\n", SDL_GetError());
		return tex;
	}
	else 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[Sprite Creation Success]");
	}
	SDL_FreeSurface(surface);
	return tex;
}

SDL_Texture* Graphics::CreateTextSprite(TTF_Font* font, string text, SDL_Color color) 
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surface == NULL) 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[Text Render Error: %s]\n", TTF_GetError());
		return NULL;
	}
	else 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[Text Render Success]");
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surface);
	if (tex == NULL) 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[Sprite Text Creation Error: %s]\n", SDL_GetError());
		return NULL;
	}
	else 
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "[Text Sprite Creation Success]");
	}
	SDL_FreeSurface(surface);
	return tex;
}

void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(ren);
}

void Graphics::DrawSprite(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(ren, tex, clip, rend, angle, NULL, flip);
}

void Graphics::DrawLine(float startX, float startY, float endX, float endY) 
{
	SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(ren, startX, startY, endX, endY);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Graphics::Render() 
{
	SDL_RenderPresent(ren);
}