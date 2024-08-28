#include "../Headers/LevelManager.h"

LevelManager::LevelManager(int stage, GameUI* sidebar, Player* player) 
{
	gameTimer = GameTimer::Instance();
	screenText = sidebar;
	screenText->SetLevel(stage);

	mStage = stage;
	playerOne = player;
	isPlayerHit = false;
	respawnDelay = 3.0f;
	respawnTimer = 0.0f;
	playerRespawnShown = 2.0f;

	gameOverScreenText = new Sprite("GAME OVER", "VT323-Regular.ttf", 64, { 150, 0, 0 });
	gameOverScreenText->Parent(this);
	gameOverScreenText->Pos(Vector2(Graphics::Instance()->windowWidth * 0.5f, Graphics::Instance()->windowHeight * 0.5f));

	gameOver = false;
	endDelay = 6.0f;
	endTimer = 0.0f;
	gameOverTextShown = 1.0f;

	currentState = running;
	lineup = new Formation();
	lineup->Pos(Vector2(Graphics::Instance()->windowWidth * 0.4, 150.0f));

	Enemy::SetFormation(lineup);
	alienNum = 0;
	Enemy::CurrentPlayer(playerOne);
}

LevelManager::~LevelManager() 
{
	gameTimer = NULL;
	screenText = NULL;
	playerOne = NULL;

	delete gameOverScreenText;
	gameOverScreenText = NULL;

	delete lineup;
	lineup = NULL;

	for (int i = 0; i < aliens.size(); i++) 
	{
		delete aliens[i];
		aliens[i] = NULL;
	}
}

void LevelManager::StartStage() 
{
	mStageStarted = true;
}

void LevelManager::HandleStartLabels()
{
	StartStage();
	playerOne->Active(true);
	playerOne->Visible(true);
}

void LevelManager::HandleCollisions() 
{
	if (!isPlayerHit)
	{
		if (playerOne->WasHit())
		{
			screenText->SetHearts(playerOne->Lives());
			isPlayerHit = true;
			respawnTimer = 0.0f;
			playerOne->Active(false);
		}
	}
}

void LevelManager::HandlePlayerDeath() 
{
	if (!playerOne->IsAnimating()) 
	{
		if (playerOne->Lives() > 0)
		{
			if (respawnTimer == 0.0f)
				playerOne->Visible(false);
			respawnTimer += gameTimer->DeltaTime();
			if (respawnTimer >= respawnDelay) 
			{
				playerOne->Active(true);
				playerOne->Visible(true);
				isPlayerHit = false;
			}
		}
		else
		{
			if (endTimer == 0.0f)
				playerOne->Visible(false);
			endTimer += gameTimer->DeltaTime();
			if (endTimer >= endDelay)
			{
				currentState = gameover;
			}
		}
	}
}

void LevelManager::HandleEnemySpawning() 
{
	if (alienNum < max_aliens)
		aliens.push_back(new Alien(alienNum, 0, false));
	alienNum++;
}

void LevelManager::HandleEnemyFormation()
{
	lineup->Update();
	bool levelCleared = false;
	if (alienNum == max_aliens)
	{
		bool flyIn = false;
		for (int i = 0; i < aliens.size(); i++) 
		{
			if (aliens[i]->CurrentState() == Enemy::flyIn)
				flyIn = true;
		}
		if (!flyIn)
		{
			lineup->Lock();
		}
	}
}

void LevelManager::HandleEnemyDiving()
{
}

LevelManager::LEVEL_STATES LevelManager::State()
{
	return currentState;
}

void LevelManager::Update()
{
	if (!mStageStarted)
	{
		HandleStartLabels();
	}
	else
	{
		HandleEnemySpawning();
		HandleEnemyFormation();
		HandleEnemyDiving();

		for (int i = 0; i < aliens.size(); i++)
			aliens[i]->Update();
		HandleCollisions();

		if (isPlayerHit) 
		{
			HandlePlayerDeath();
		}
		else
		{
			if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N)) 
			{
				currentState = finished;
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[Next wave]");
			}
		}
	}
}

void LevelManager::Render()
{
	for (int i = 0; i < aliens.size(); i++)
		aliens[i]->Render();
	if (isPlayerHit) 
	{
		if (respawnTimer >= playerRespawnShown)
			gameReadyText->Render();
		if (endTimer >= gameOverTextShown)
			gameOverScreenText->Render();
	}
}