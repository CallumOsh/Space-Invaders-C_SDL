#ifndef aSpriteFile
#define aSpriteFile

#include "GameEntity.h"
#include "AssetManager.h"

using namespace std;

class Sprite : public GameEntity 
{

protected:
	SDL_Texture* texture;
	Graphics* graphics;
	int rectWidth;
	int rectHeight;
	bool isClipped;
	SDL_Rect renderRect;
	SDL_Rect newClipRect;

public:
	Sprite(string filename);
	Sprite(string filename, int x, int y, int w, int h);
	Sprite(string text, string fontpath, int size, SDL_Color color);
	~Sprite();
	Vector2 ScaledDimensions();
	virtual void Render();
};
#endif
