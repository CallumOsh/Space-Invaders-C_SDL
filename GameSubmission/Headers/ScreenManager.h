#ifndef aScreenManagerFile
#define aScreenManagerFile

#include "Menu.h"
#include "GameScreen.h"

class ScreenManager 
{

private:
	enum SCREENS { start, play };
	static ScreenManager* instance;
	InputManager* inputManager;
	AudioManager* audioManager;
	Menu* menuScreen;
	GameScreen* gameScreen;
	SCREENS currentScreen;

public:
	static ScreenManager* Instance();
	static void Clean();
	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();
};
#endif