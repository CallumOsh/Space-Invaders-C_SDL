#ifndef aLevelManager
#define aLevelManager

#include "InputManager.h"
#include "GameUI.h"
#include "Player.h"
#include "Alien.h"

using namespace std;

class LevelManager : public GameEntity 
{

public:
	enum LEVEL_STATES { running, finished, gameover };

private:
	GameTimer* gameTimer;
	GameUI* screenText;

	int mStage;
	bool mStageStarted;
	float textTimer;

	Sprite* waveText;
	ScoreManager* waveNum;
	float waveTextShown;
	float waveTextHidden;
	Sprite* gameReadyText;
	float gameReadyTextShown;
	float gameReadyTextHidden;


	Player* playerOne;
	bool isPlayerHit;
	float respawnDelay;
	float respawnTimer;
	float playerRespawnShown;

	Sprite* gameOverScreenText;
	bool gameOver;
	float endDelay;
	float endTimer;
	float gameOverTextShown;

	LEVEL_STATES currentState;
	Formation* lineup;
	const int max_aliens = 16;
	int alienNum;
	vector<Enemy*> aliens;

private:
	void StartStage();
	void HandleStartLabels();
	void HandleCollisions();
	void HandlePlayerDeath();
	void HandleEnemySpawning();
	void HandleEnemyFormation();
	void HandleEnemyDiving();

public:

	LevelManager(int stage, GameUI* screenText, Player* player);
	~LevelManager();
	LEVEL_STATES State();
	void Update();
	void Render();
};
#endif
