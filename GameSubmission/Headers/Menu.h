#ifndef aMenuFile
#define aMenuFile

#include "AnimatedSprite.h"
#include "InputManager.h"
#include "ScoreManager.h"
#include "AudioManager.h"

class Menu : public GameEntity 
{

private:
	GameTimer* gameTimer;
	InputManager* inputManager;
	AudioManager* audioManager;

	Sprite* gameTitle;
	GameEntity* menu;
	Sprite* play;
	Sprite* options;
	Sprite* exit;
	AnimatedSprite* animAlienImage;
	Sprite* pointer;
	Vector2 pointerStart;
	Vector2 pointerOffset;
	int pointerSelect;
	GameEntity* nameIdBar;
	Sprite* nameId;

public:
	Menu();
	~Menu();
	int SelectedOption();
	void ChangeSelectedOption(int change);
	void Update();
	void Render();
};
#endif
