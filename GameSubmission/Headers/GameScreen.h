#ifndef aGameScreenFile
#define aGameScreenFile

#include "LevelManager.h"

class GameScreen : public GameEntity 
{

private:
	GameTimer* timer;
	InputManager* inputManager;
	AudioManager* audioManager;

	GameUI* screenText;
	Sprite* background;

	float startTimer;
	float gameDelay;

	bool isStarted;

	LevelManager* wave;
	bool levelStart;
	int currentLevel;

	Player* player;
	void StartNewWave();

public:

	GameScreen();
	~GameScreen();
	void StartNewGame();
	bool GameOver();
	void Update();
	void Render();
};
#endif
