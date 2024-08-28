#include "../Headers/Sprite.h"

Sprite::Sprite(string filename) 
{
	graphics = Graphics::Instance();
	texture = AssetManager::Instance()->GetSprite(filename);
	SDL_QueryTexture(texture, NULL, NULL, &rectWidth, &rectHeight);

	isClipped = false;
	renderRect.w = rectWidth;
	renderRect.h = rectHeight;
}

Sprite::Sprite(string filename, int x, int y, int w, int h) 
{
	graphics = Graphics::Instance();
	texture = AssetManager::Instance()->GetSprite(filename);

	isClipped = true;
	rectWidth = w;
	rectHeight = h;
	renderRect.w = rectWidth;
	renderRect.h = rectHeight;
	newClipRect.x = x;
	newClipRect.y = y;
	newClipRect.w = rectWidth;
	newClipRect.h = rectHeight;
}

Sprite::Sprite(string text, string fontPath, int size, SDL_Color color) 
{
	graphics = Graphics::Instance();
	texture = AssetManager::Instance()->GetScreenText(text, fontPath, size, color);

	isClipped = false;
	SDL_QueryTexture(texture, NULL, NULL, &rectWidth, &rectHeight);
	renderRect.w = rectWidth;
	renderRect.h = rectHeight;
}

Sprite::~Sprite()
{
	texture = NULL;
	graphics = NULL;
}

Vector2 Sprite::ScaledDimensions() 
{
	Vector2 scaledDimensions = Scale();
	scaledDimensions.x *= rectWidth;
	scaledDimensions.y *= rectHeight;
	return scaledDimensions;
}

void Sprite::Render() 
{
	Vector2 pos = Pos(world);
	Vector2 scale = Scale(world);
	renderRect.x = (int)(pos.x - rectWidth * scale.x * 0.5f);
	renderRect.y = (int)(pos.y - rectHeight * scale.y * 0.5f);
	renderRect.w = (int)(rectWidth * scale.x);
	renderRect.h = (int)(rectHeight * scale.y);

	graphics->DrawSprite(texture, (isClipped) ? &newClipRect : NULL, &renderRect, Rotation(world));
}