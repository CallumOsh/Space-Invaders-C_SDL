#include <string.h>
#include "../Headers/InputManager.h"

InputManager* InputManager::instance = NULL;

InputManager* InputManager::Instance() 
{
	if (instance == NULL)
		instance = new InputManager();
	return instance;
}

void InputManager::Clean() 
{
	delete instance;
	instance = NULL;
}

InputManager::InputManager()
{
	keyboardState = SDL_GetKeyboardState(&keyLength);
	prevKeyboard = new Uint8[keyLength];
	memcpy(prevKeyboard, keyboardState, keyLength);
}

InputManager::~InputManager() 
{
	delete[] prevKeyboard;
	prevKeyboard = NULL;
}

bool InputManager::KeyDown(SDL_Scancode scanCode) 
{
	return (keyboardState[scanCode] != 0);
}

bool InputManager::KeyPressed(SDL_Scancode scanCode) 
{
	return (prevKeyboard[scanCode]) == 0 && (keyboardState[scanCode] != 0);
}

bool InputManager::KeyReleased(SDL_Scancode scanCode) 
{
	return (prevKeyboard[scanCode] != 0) && (keyboardState[scanCode] == 0);
}

void InputManager::Update() 
{
}

void InputManager::UpdatePrevInput() 
{
	memcpy(prevKeyboard, keyboardState, keyLength);
}
