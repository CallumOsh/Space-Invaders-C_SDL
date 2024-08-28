#ifndef aGameTimerFile
#define aGameTimerFile

#include "SDL.h"

class GameTimer
{

private:
	static GameTimer* instance;
	unsigned int startTicks;
	unsigned int elapsedTicks;
	float deltaTime;
	float aTimeScale;

public:
	static GameTimer* Instance();
	static void Clean();
	void Reset();
	float DeltaTime();
	void TimeScale(float t = 1.0f);
	float TimeScale();

	void Update();

private:
	GameTimer();
	~GameTimer();
};
#endif