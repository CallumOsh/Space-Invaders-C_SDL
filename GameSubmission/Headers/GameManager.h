#ifndef aGameManagerFile
#define aGameManagerFile

#include "AudioManager.h"
#include "GameTimer.h"
#include "ScreenManager.h"
#include "InputManager.h"
#include "PhysicsManager.h"

class GameManager
{

private:
	static GameManager* instance;
	const int frameRate = 60;
	bool quit;

	Graphics* graphics;
	AssetManager* assetManager;
	InputManager* inputManager;
	AudioManager* audioManager;
	PhysicsManager* physicsManager;
	ScreenManager* screenManager;
	GameTimer* gameTimer;
	SDL_Event events;

public:
	static GameManager* Instance();
	static void Clean();
	void Run();

private:
	GameManager();
	~GameManager();
	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void Render();
};
#endif