#pragma once
#include "SDL.h"
#include <vector>
#include <iostream>
#include "Vector2.h"

struct KeyAxis
{
	SDL_KeyCode lowKey;
	float lowValue;

	SDL_KeyCode highKey;
	float highValue;

	float value;

	KeyAxis(SDL_KeyCode lowKey, float lowValue, SDL_KeyCode highKey, float highValue)
		: lowKey(lowKey), lowValue(lowValue), highKey(highKey), highValue(highValue)
	{
		value = 0.0f;
	}
};

struct KeyAxis2D
{
	KeyAxis horizontal;
	KeyAxis vertical;
	
	Vector2 value;
	Vector2 GetValueInvertedY()
	{
		return Vector2(value.x, -value.y);
	}

	std::string name;

	KeyAxis2D(const std::string& axisName, KeyAxis horizontal, KeyAxis vertical) : name(axisName), horizontal(horizontal), vertical(vertical)
	{
		value = Vector2::zero;
	}
};


struct Keybinding
{
	SDL_Keycode keyCode;
	bool pressed;

	std::string name;

	Keybinding(const std::string& name, SDL_Keycode keyCode, bool pressed) : name(name), keyCode(keyCode), pressed(pressed)
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

	void ProcessKeyEvent(SDL_Event e);
	void RegisterBinding(Keybinding newBinding);
	void RegisterAxis2D(KeyAxis2D newAxis);
	void ClearBindings();
	void ClearAxes();

	void DebugPrintBindingsState();

	KeyAxis2D*  Find2DAxisByName(const std::string& name);
	Keybinding* FindBindingByName(const std::string& name);

private:
	static InputManager* instance;

	InputManager();
	~InputManager();

	std::vector<Keybinding> bindings;
	std::vector<KeyAxis2D> axes2D;
};

