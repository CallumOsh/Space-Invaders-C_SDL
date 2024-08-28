#include "../Headers/AnimatedSprite.h"


AnimatedSprite::AnimatedSprite(string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir)
	: Sprite(filename, x, y, w, h)
{
	gameTimer = GameTimer::Instance();
	startX = x;
	startY = y;
	frameCount = frameCount;
	animSpeed = animationSpeed;
	timerPerFrame = animSpeed / frameCount;
	animTimer = 0.0f;
	animDir = animationDir;
	isAnimDone = false;
	animWrapMode = loop;
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::WrapMode(WRAP_MODE mode)
{
	animWrapMode = mode;
}

void AnimatedSprite::ResetAnimation()
{
	animTimer = 0.0f;
	isAnimDone = false;
}

bool AnimatedSprite::IsAnimating() 
{
	return !isAnimDone;
}

void AnimatedSprite::Update() 
{
	if (!isAnimDone) 
	{
		animTimer += gameTimer->DeltaTime();
		if (animTimer >= animSpeed)
		{
			if (animWrapMode == loop) 
			{
				animTimer -= animSpeed;
			}
			else 
			{
				isAnimDone = true;
				animTimer = animSpeed - timerPerFrame;
			}
		}

		if (animDir == horizontal) 
		{
			newClipRect.x = startX + (int)(animTimer / timerPerFrame) * rectWidth;
		}
		else 
		{
			newClipRect.y = startY + (int)(animTimer / timerPerFrame) * rectHeight;
		}
	}
}