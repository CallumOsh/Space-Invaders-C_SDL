#ifndef aGameUIFile
#define aGameUIFile

#include "GameTimer.h"
#include "ScoreManager.h"
#include "AudioManager.h"

class GameUI : public GameEntity {

private:
	GameTimer* gameTimer;
	AudioManager* audioManager;

	Sprite* playerScoreText;
	ScoreManager* playerScore;

	static const int MAX_HEARTS = 3;
	GameEntity* playerHearts;
	Sprite* hearts;
	Sprite* heartSprites[MAX_HEARTS];
	int totalHearts;

	int levelsLeft;

public:
	GameUI();
	~GameUI();
	void SetPlayerScore(int score);
	void SetHearts(int hearts);
	void SetLevel(int level);
	void Render();
};
#endif