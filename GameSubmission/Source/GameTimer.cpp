#include "../Headers/GameTimer.h"

GameTimer* GameTimer::instance = NULL;

GameTimer* GameTimer::Instance() 
{
	if (instance == NULL)
		instance = new GameTimer();
	return instance;
}

void GameTimer::Clean() 
{
	delete instance;
	instance = NULL;
}

GameTimer::GameTimer()
{
	Reset();
	aTimeScale = 1.0f;
}

GameTimer::~GameTimer()
{
}

void GameTimer::Reset() 
{
	startTicks = SDL_GetTicks();
	elapsedTicks = 0;
	deltaTime = 0.0f;
}

float GameTimer::DeltaTime() 
{
	return deltaTime;
}

void GameTimer::TimeScale(float t)
{
	aTimeScale = t;
}

float GameTimer::TimeScale()
{
	return aTimeScale;
}

void GameTimer::Update()
{
	elapsedTicks = SDL_GetTicks() - startTicks;
	deltaTime = elapsedTicks * 0.001f;
}