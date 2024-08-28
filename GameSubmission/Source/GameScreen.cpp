#include "../Headers/GameScreen.h"

GameScreen::GameScreen() 
{
	timer = GameTimer::Instance();
	inputManager = InputManager::Instance();
	audioManager = AudioManager::Instance();

	screenText = new GameUI();
	screenText->Parent(this);
	screenText->Pos(Vector2(Graphics::Instance()->windowWidth * 0.85f, Graphics::Instance()->windowHeight * 0.05f));

	background = new Sprite("backg.png");
	background->Pos(Vector2(Graphics::Instance()->windowWidth*0.5f, Graphics::Instance()->windowHeight*0.5f));
	background->Parent(this);

	wave = NULL;
	gameDelay = 0.5f;
	levelStart = false;

	player = NULL;
	Enemy::CreatePaths();
}

GameScreen::~GameScreen()
{
	timer = NULL;
	inputManager = NULL;
	audioManager = NULL;

	delete screenText;
	screenText = NULL;

	delete background;
	background = NULL;

	delete wave;
	wave = NULL;

	delete player;
	player = NULL;
}

void GameScreen::StartNewWave() 
{
	currentLevel++;
	startTimer = 0.0f;
	levelStart = true;
	delete wave;
	wave = new LevelManager(currentLevel, screenText, player);
}

void GameScreen::StartNewGame() 
{
	delete player;
	player = new Player();
	player->Parent(this);
	player->Pos(Vector2(Graphics::Instance()->windowWidth * 0.5f, Graphics::Instance()->windowHeight * 0.95f));
	player->Active(false);

	screenText->SetHearts(player->Lives());
	screenText->SetPlayerScore(player->Score());
	screenText->SetLevel(0);

	isStarted = false;
	levelStart = false;
	startTimer = 0.0f;
	currentLevel = 0;
}

bool GameScreen::GameOver() 
{
	if (!levelStart)
		return false;
	return (wave->State() == LevelManager::gameover);
}

void GameScreen::Update() 
{
	isStarted = true;
	if (isStarted)
	{
		if (!levelStart) 
		{
			startTimer += timer->DeltaTime();
			if (startTimer >= gameDelay)
				StartNewWave();
		}
	}

	if (isStarted)
	{
		if (currentLevel > 0)
			screenText->Update();
		if (levelStart) 
		{
			wave->Update();
			if (wave->State() == LevelManager::finished)
			{
				levelStart = false;
			}
		}
		player->Update();
		screenText->SetPlayerScore(player->Score());
	}
}

void GameScreen::Render() 
{
	background->Render();
	screenText->Render();

	if (isStarted) 
	{
		if (levelStart)
			wave->Render();
		player->Render();
	}
}