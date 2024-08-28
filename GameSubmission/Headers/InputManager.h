#ifndef aInputManager
#define aInputManager

#include "SDL.h"
#include "MathHelper.h"

class InputManager
{

private:
	static InputManager* instance;
	Uint8* prevKeyboard;
	const Uint8* keyboardState;
	int keyLength;

public:
	static InputManager* Instance();
	static void Clean();
	bool KeyDown(SDL_Scancode scanCode);
	bool KeyPressed(SDL_Scancode scanCode);
	bool KeyReleased(SDL_Scancode scanCode);
	void Update();
	void UpdatePrevInput();

private:
	InputManager();
	~InputManager();
};
#endif