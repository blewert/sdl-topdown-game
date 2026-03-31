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
}

InputManager::~InputManager()
{
	this->ClearBindings();
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


}

void InputManager::RegisterBinding(Keybinding newBinding)
{
	bindings.push_back(newBinding);
}

void InputManager::ClearBindings()
{
	bindings.clear();
}

void InputManager::DebugPrintBindingsState()
{
	for (const Keybinding& binding : bindings)
	{
		std::cout << "Binding [" << binding.keyCode << "]: " << binding.pressed << std::endl;
	}

	std::cout << std::endl;
}

void InputManager::Update(SDL_Event event)
{
	if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN)
		this->ProcessKeyEvent(event);
}
