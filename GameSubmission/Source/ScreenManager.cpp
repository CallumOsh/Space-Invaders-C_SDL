#include "../Headers/ScreenManager.h"

ScreenManager* ScreenManager::instance = NULL;

ScreenManager* ScreenManager::Instance()
{
	if (instance == NULL)
		instance = new ScreenManager();
	return instance;
}

void ScreenManager::Clean() 
{
	delete instance;
	instance = NULL;
}

ScreenManager::ScreenManager() 
{
	inputManager = InputManager::Instance();
	audioManager = AudioManager::Instance();

	menuScreen = new Menu();
	gameScreen = new GameScreen();
	currentScreen = start;
}

ScreenManager::~ScreenManager() 
{
	inputManager = NULL;
	audioManager = NULL;

	delete menuScreen;
	menuScreen = NULL;

	delete gameScreen;
	gameScreen = NULL;
}

void ScreenManager::Update() 
{
	switch (currentScreen) 
	{
	case start:
		menuScreen->Update();
		if (inputManager->KeyPressed(SDL_SCANCODE_SPACE))
		{
			currentScreen = play;
			gameScreen->StartNewGame();
			audioManager->PlayGameMusic("Menu.wav");
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[Game Screen Loaded]");
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[Background Music Playing]");
		}
		break;
	case play:
		gameScreen->Update();
		if (gameScreen->GameOver()) 
		{
			currentScreen = start;
		}
		break;
	}
}

void ScreenManager::Render() 
{
	switch (currentScreen)
	{
	case start:
		menuScreen->Render();
		break;
	case play:
		gameScreen->Render();
		break;
	}
}