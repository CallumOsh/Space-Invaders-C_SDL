#ifndef aAnimatedSpriteFile
#define aAnimatedSpriteFile

#include "GameTimer.h"
#include "Sprite.h"

using namespace std;

class AnimatedSprite : public Sprite {

public:
	enum WRAP_MODE { once = 0, loop = 1 };
	enum ANIM_DIR { horizontal = 0, vertical = 1 };

private:
	GameTimer* gameTimer;
	int startX;
	int startY;

	float animTimer;
	float animSpeed;
	float timerPerFrame;
	int frameCount;

	WRAP_MODE animWrapMode;
	ANIM_DIR animDir;
	bool isAnimDone;

public:
	AnimatedSprite(string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir);
	~AnimatedSprite();
	void WrapMode(WRAP_MODE mode);
	void ResetAnimation();
	bool IsAnimating();
	void Update();
};
#endif