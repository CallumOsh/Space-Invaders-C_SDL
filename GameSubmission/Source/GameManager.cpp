#include "../Headers/GameManager.h"
#include <time.h>

GameManager* GameManager::instance = NULL;

GameManager* GameManager::Instance()
{
	if (instance == NULL)
		instance = new GameManager();
	return instance;
}

void GameManager::Clean() 
{
	delete instance;
	instance = NULL;
}

GameManager::GameManager()
{
	srand((Uint8)time(0));
	quit = false;

	graphics = Graphics::Instance();
	if (!Graphics::Initialized())
		quit = true;

	assetManager = AssetManager::Instance();
	inputManager = InputManager::Instance();
	audioManager = AudioManager::Instance();
	gameTimer = GameTimer::Instance();
	screenManager = ScreenManager::Instance();

	physicsManager = PhysicsManager::Instance();
	physicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Friendly, PhysicsManager::CollisionFlags::Hostile | PhysicsManager::CollisionFlags::HostileProjectiles);
	physicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::FriendlyProjectiles, PhysicsManager::CollisionFlags::Hostile);
	physicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Hostile, PhysicsManager::CollisionFlags::Friendly | PhysicsManager::CollisionFlags::FriendlyProjectiles);
	physicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::HostileProjectiles, PhysicsManager::CollisionFlags::Friendly);
}

GameManager::~GameManager()
{
	ScreenManager::Clean();
	screenManager = NULL;

	PhysicsManager::Clean();
	physicsManager = nullptr;

	AudioManager::Clean();
	audioManager = NULL;

	AssetManager::Clean();
	assetManager = NULL;

	Graphics::Clean();
	graphics = NULL;

	InputManager::Clean();
	inputManager = NULL;

	GameTimer::Clean();
	gameTimer = NULL;
}

void GameManager::EarlyUpdate() 
{
	inputManager->Update();
}

void GameManager::Update() 
{
	screenManager->Update();
}

void GameManager::LateUpdate()
{
	physicsManager->Update();
	inputManager->UpdatePrevInput();
	gameTimer->Reset();
}

void GameManager::Render() 
{
	graphics->ClearBackBuffer();
	screenManager->Render();
	graphics->Render();
}

void GameManager::Run()
{
	while (!quit) 
	{
		gameTimer->Update();
		inputManager->Update();
		while (SDL_PollEvent(&events) != 0)
		{
			if (events.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (inputManager->KeyDown(SDL_SCANCODE_ESCAPE))
			{
				quit = true;
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[Escape Key Pressed, Game Ended]");
			}
			else if (inputManager->KeyPressed(SDL_SCANCODE_M))
			{
				audioManager->PauseGameMusic();
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[M Pressed, Background Music Muted]");
			}
		}
		if (gameTimer->DeltaTime() >= (1.0f / frameRate))
		{
			EarlyUpdate();
			Update();
			LateUpdate();
			Render();
		}
	}
}