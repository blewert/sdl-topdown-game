#pragma once
#include "SDL.h"
#include "Vector2.h"
#include <vector>
#include <iostream>

struct KeyAxis
{
	SDL_KeyCode lowKey;
	float lowValue;

	SDL_KeyCode highKey;
	float highValue;

	KeyAxis(SDL_KeyCode lowKey, float lowValue, SDL_KeyCode highKey, float highValue)
		: lowKey(lowKey), lowValue(lowValue), highKey(highKey), highValue(highValue)
	{

	}
};

struct Keybinding
{
	SDL_Keycode keyCode;
	bool pressed;

	Keybinding(SDL_Keycode keyCode, bool pressed) : keyCode(keyCode), pressed(pressed)
	{

	}
};

class InputManager
{
public:
	static inline InputManager& Instance()
	{
		if (instance == nullptr)
			instance = new InputManager();

		return *InputManager::instance;
	}

	static void Exit();
	void Update(SDL_Event event);

	Vector2 wasdAxis;

	void ProcessKeyEvent(SDL_Event e);
	void RegisterBinding(Keybinding newBinding);
	void ClearBindings();

	void DebugPrintBindingsState();

private:
	static InputManager* instance;

	InputManager();
	~InputManager();

	std::vector<Keybinding> bindings;
};

