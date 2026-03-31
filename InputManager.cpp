#include "InputManager.h"


InputManager* InputManager::instance = nullptr;

void InputManager::Exit()
{
	delete instance;
}

InputManager::InputManager()
{
	this->RegisterBinding(Keybinding(SDLK_w, false));
	this->RegisterBinding(Keybinding(SDLK_a, false));
	this->RegisterBinding(Keybinding(SDLK_s, false));
	this->RegisterBinding(Keybinding(SDLK_d, false));

	this->RegisterBinding(Keybinding(SDLK_UP,    false));
	this->RegisterBinding(Keybinding(SDLK_LEFT,  false));
	this->RegisterBinding(Keybinding(SDLK_DOWN,  false));
	this->RegisterBinding(Keybinding(SDLK_RIGHT, false));

	KeyAxis wasdHoriz = KeyAxis(SDLK_a, -1, SDLK_d, 1);
	KeyAxis wasdVert  = KeyAxis(SDLK_s, -1, SDLK_w, 1);

	KeyAxis uldrHoriz = KeyAxis(SDLK_LEFT, -1, SDLK_RIGHT, 1);
	KeyAxis uldrVert  = KeyAxis(SDLK_DOWN, -1, SDLK_UP, 1);

	this->RegisterAxis2D(KeyAxis2D(wasdHoriz, wasdVert));
	this->RegisterAxis2D(KeyAxis2D(uldrHoriz, uldrVert));
}

InputManager::~InputManager()
{
	this->ClearBindings();
	this->ClearAxes();
}

void InputManager::ProcessKeyEvent(SDL_Event e)
{
	for (Keybinding& binding : bindings)
	{
		if (binding.keyCode == e.key.keysym.sym)
		{
			binding.pressed = (e.type == SDL_KEYDOWN);
		}
	}

	for (KeyAxis2D& axis : axes2D)
	{
		KeyAxis* axes[] { &axis.horizontal, &axis.vertical };
		
		for (KeyAxis* lohiAxis : axes)
		{
			float value = 0.0f;

			//Nothing to do with this axis? Skip it
			if (lohiAxis->highKey != e.key.keysym.sym && lohiAxis->lowKey != e.key.keysym.sym)
			{
				continue;
			}

			//Otherwise assign high if high pressed
			if (lohiAxis->highKey == e.key.keysym.sym)
				value = (e.type == SDL_KEYDOWN) ? (lohiAxis->highValue) : (0.0f);

			//Or low if low pressed
			else if (lohiAxis->lowKey == e.key.keysym.sym)
				value = (e.type == SDL_KEYDOWN) ? (lohiAxis->lowValue) : (0.0f);

			//Change underlying value
			lohiAxis->value = value;
		}

		//Finally build 2D composite axis
		axis.value = Vector2(axis.horizontal.value, axis.vertical.value);
	}
}

void InputManager::RegisterBinding(Keybinding newBinding)
{
	bindings.push_back(newBinding);
}

void InputManager::RegisterAxis2D(KeyAxis2D newAxis)
{
	this->axes2D.push_back(newAxis);
}

void InputManager::ClearAxes()
{
	this->axes2D.clear();
}

void InputManager::ClearBindings()
{
	bindings.clear();
}

void InputManager::DebugPrintBindingsState()
{
	//for (const Keybinding& binding : bindings)
	//{
		//std::cout << "Binding [" << binding.keyCode << "]: " << binding.pressed << std::endl;
	//} 

	for (const KeyAxis2D& axis : axes2D)
	{
		std::cout << "axis: " << axis.value.ToString() << std::endl;
	}

	std::cout << std::endl;
}

void InputManager::Update(SDL_Event event)
{
	if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN)
		this->ProcessKeyEvent(event);
}
