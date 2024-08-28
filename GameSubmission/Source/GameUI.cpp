#include "../Headers/GameUI.h"

GameUI::GameUI() 
{
	gameTimer = GameTimer::Instance();
	audioManager = AudioManager::Instance();

	playerScoreText = new Sprite("Score:", "VT323-Regular.ttf", 32, { 255, 255, 255 });
	playerScoreText->Parent(this);
	playerScoreText->Pos(Vector2(-750.0f, -10.0f));

	playerScore = new ScoreManager;
	playerScore->Parent(this);
	playerScore->Pos(Vector2(-630.0f, -10.0f));

	hearts = new Sprite("Lives:", "VT323-Regular.ttf", 32, { 255, 255, 255 });
	hearts->Parent(this);
	hearts->Pos(Vector2(-100.0f, -10.0f));

	playerHearts = new GameEntity();
	playerHearts->Parent(this);
	playerHearts->Pos(Vector2(0.0f, -10.0f));
	playerHearts->Scale(Vector2(0.7f, 0.7f));

	for (int i = 0; i < MAX_HEARTS; i++) 
	{
		heartSprites[i] = new Sprite("ArcadeHeart.png");
		heartSprites[i]->Parent(playerHearts);
		heartSprites[i]->Pos(Vector2(62.0f * (i % 3), 70.0f * (i / 3)));
	}
}

GameUI::~GameUI() 
{
	gameTimer = NULL;
	audioManager = NULL;

	delete playerScoreText;
	playerScoreText = NULL;

	delete playerScore;
	playerScore = NULL;

	delete hearts;
	hearts = NULL;

	delete playerHearts;
	playerHearts = NULL;

	for (int i = 0; i < MAX_HEARTS; i++) {
		delete heartSprites[i];
		heartSprites[i] = NULL;
	}
}

void GameUI::SetPlayerScore(int score) 
{
	playerScore->Score(score);
}

void GameUI::SetHearts(int ships) 
{
	totalHearts = ships;
}

void GameUI::SetLevel(int level) 
{
	levelsLeft = level;
}

void GameUI::Render()
{
	playerScoreText->Render();
	playerScore->Render();
	hearts->Render();

	for (int i = 0; i < MAX_HEARTS && i < totalHearts; i++)
		heartSprites[i]->Render();
}