#include "../Headers/Menu.h"

Menu::Menu() 
{
	gameTimer = GameTimer::Instance();
	inputManager = InputManager::Instance();
	audioManager = AudioManager::Instance();

	gameTitle = new Sprite("Territory Intruders", "VT323-Regular.ttf", 64, { 230, 230, 230 });
	gameTitle->Pos(Vector2(Graphics::Instance()->windowWidth * 0.5f, Graphics::Instance()->windowHeight * 0.15f));
	gameTitle->Parent(this);

	menu = new GameEntity(Vector2(Graphics::Instance()->windowWidth * 0.3f, Graphics::Instance()->windowHeight * 0.475f));
	play = new Sprite("Play", "VT323-Regular.ttf", 64, { 230, 230, 230 });
	options = new Sprite("Options", "VT323-Regular.ttf", 64, { 230, 230, 230 });
	exit = new Sprite("Exit", "VT323-Regular.ttf", 64, { 230, 230, 230 });

	animAlienImage = new AnimatedSprite("AlienFlash.png", 0, 0, 64, 64, 3, 0.5f, AnimatedSprite::vertical);

	pointer = new Sprite("Cursor.png");

	play->Parent(menu);
	options->Parent(menu);
	exit->Parent(menu);
	animAlienImage->Parent(menu);
	pointer->Parent(menu);

	play->Pos(Vector2(-40.0f, -35.0f));
	options->Pos(Vector2(0.0f, 35.0f));
	exit->Pos(Vector2(-40.0f, 105.0f));
	animAlienImage->Pos(Vector2(375.0f, 40.0f));
	pointer->Pos(Vector2(-170.0f, -25.0f));

	animAlienImage->Scale(Vector2(4.0f, 4.0f));
	menu->Parent(this);
	pointerStart = Vector2(pointer->Pos(local));
	pointerOffset = Vector2(0.0f, 70.0f);
	pointerSelect = 0;

	nameIdBar = new GameEntity(Vector2(Graphics::Instance()->windowWidth * 0.5f, Graphics::Instance()->windowHeight * 0.7f));
	nameId = new Sprite("Callum O'Shaughnessy 16641760", "VT323-Regular.ttf", 32, { 230, 230, 230 });
	nameId->Pos(Vector2(Graphics::Instance()->windowWidth*0.5, Graphics::Instance()->windowHeight*0.9));

	nameId->Parent(nameIdBar);
	nameIdBar->Parent(this);
}

Menu::~Menu() 
{
	delete gameTitle;
	gameTitle = NULL;

	delete menu;
	menu = NULL;

	delete play;
	play = NULL;

	delete options;
	options = NULL;

	delete exit;
	exit = NULL;

	delete animAlienImage;
	animAlienImage = NULL;

	delete pointer;
	pointer = NULL;

	delete nameIdBar;
	nameIdBar = NULL;

	delete nameId;
	nameId = NULL;
}

int Menu::SelectedOption() 
{
	return pointerSelect;
}

void Menu::ChangeSelectedOption(int change)
{
	pointerSelect += change;

	if (pointerSelect < 0)
		pointerSelect = 2;
	else if (pointerSelect > 2)
		pointerSelect = 0;
	pointer->Pos(pointerStart + pointerOffset * pointerSelect);
}

void Menu::Update()
{
	if (inputManager->KeyPressed(SDL_SCANCODE_DOWN)) {
		ChangeSelectedOption(1);
		audioManager->PlayGameEffects("MenuSelect.wav");
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[Pointer at New Position]");
	}
	else if (inputManager->KeyPressed(SDL_SCANCODE_UP)) {
		ChangeSelectedOption(-1);
		audioManager->PlayGameEffects("MenuSelect.wav");
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[Pointer at New Position]");
	}
	animAlienImage->Update();
}

void Menu::Render() 
{	
	gameTitle->Render();
	play->Render();
	options->Render();
	exit->Render();
	animAlienImage->Render();
	pointer->Render();
	nameId->Render();
}