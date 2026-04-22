#include "InputManager.h"
#include "Camera.h"
#include "Scene.h"

InputManager* InputManager::instance = nullptr;

void InputManager::Exit()
{
	delete instance;
}

InputManager::InputManager()
{
	this->RegisterBinding(Keybinding("W", SDLK_w, false));
	this->RegisterBinding(Keybinding("A", SDLK_a, false));
	this->RegisterBinding(Keybinding("S", SDLK_s, false));
	this->RegisterBinding(Keybinding("D", SDLK_d, false));

	this->RegisterBinding(Keybinding("Up",    SDLK_UP,    false));
	this->RegisterBinding(Keybinding("Left",  SDLK_LEFT,  false));
	this->RegisterBinding(Keybinding("Down",  SDLK_DOWN,  false));
	this->RegisterBinding(Keybinding("Right", SDLK_RIGHT, false));

	KeyAxis wasdHoriz = KeyAxis(SDLK_a, -1, SDLK_d, 1);
	KeyAxis wasdVert  = KeyAxis(SDLK_s, -1, SDLK_w, 1);

	KeyAxis uldrHoriz = KeyAxis(SDLK_LEFT, -1, SDLK_RIGHT, 1);
	KeyAxis uldrVert  = KeyAxis(SDLK_DOWN, -1, SDLK_UP, 1);

	this->RegisterAxis2D(KeyAxis2D("WASD",   wasdHoriz, wasdVert));
	this->RegisterAxis2D(KeyAxis2D("Arrows", uldrHoriz, uldrVert));

	//Set up mouse data
	leftMouseDown = rightMouseDown = wasMouseDownLeft = wasMouseDownRight = false;
	mousePosition = Vector2();
	mouseDelta = Vector2();
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

			if (e.key.repeat)
				continue;

			bool isLowKey  = lohiAxis->lowKey == e.key.keysym.sym;
			bool isHighKey = lohiAxis->highKey == e.key.keysym.sym;

			if (e.type == SDL_KEYDOWN)
			{
				if (isLowKey)
				{
					value = lohiAxis->lowValue;
					lohiAxis->lowKeyDown = true;
				}
				else if (isHighKey)
				{
					value = lohiAxis->highValue;
					lohiAxis->highKeyDown = true;
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				if (isLowKey)
				{
					value = (lohiAxis->highKeyDown) ? lohiAxis->highValue : 0.0f;
					lohiAxis->lowKeyDown = false;
				}
				else if (isHighKey)
				{
					value = (lohiAxis->lowKeyDown) ? lohiAxis->lowValue : 0.0f;
					lohiAxis->highKeyDown = false;
				}
			}

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

void InputManager::ShowCursor(bool status)
{
	SDL_ShowCursor(status);
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

KeyAxis2D* InputManager::Find2DAxisByName(const std::string& name)
{
	for (KeyAxis2D& axis : axes2D)
	{
		if (axis.name == name)
			return &axis;
	}

	return nullptr;
}

Keybinding* InputManager::FindBindingByName(const std::string& name)
{
	for (Keybinding& binding : bindings)
	{
		if (binding.name == name)
			return &binding;
	}

	return nullptr;
}

Vector2 InputManager::GetMouseWorldPos(Camera* cam)
{
	Vector2 pos = this->GetMousePos();
	return cam->ScreenToWorldPos(pos);
}

Vector2 InputManager::GetMouseNormScreenPos(Camera* cam, bool centre)
{
	SDL_Renderer* renderer = cam->parentScene->GetRenderer();

	int windowW, windowH;
	SDL_Window* window = SDL_RenderGetWindow(renderer);
	SDL_GetWindowSize(window, &windowW, &windowH);

	float w, h;
	SDL_RenderWindowToLogical(renderer, windowW, windowH, &w, &h);

	Vector2 mousePos = GetMousePos();

	if (centre)
		return Vector2(mousePos.x / w, mousePos.y / h) * 2.0f - Vector2(1, 1);
	else
		return Vector2(mousePos.x / w, mousePos.y / h);
}

Vector2 InputManager::GetMousePos()
{
	return mousePosition;
}

Vector2 InputManager::GetMouseDelta()
{
	return mouseDelta;
}

bool InputManager::GetLeftMouseDown()
{
	return leftMouseDown;
}

bool InputManager::GetLeftMouseDownThisFrame()
{
	return (!wasMouseDownLeft && leftMouseDown);
}

bool InputManager::GetLeftMouseUpThisFrame()
{
	return (wasMouseDownLeft && !leftMouseDown);
}

bool InputManager::GetRightMouseDown()
{
	return rightMouseDown;
}

bool InputManager::GetRightMouseDownThisFrame()
{
	return (!wasMouseDownRight && rightMouseDown);
}

bool InputManager::GetRightMouseUpThisFrame()
{
	return (wasMouseDownRight && !rightMouseDown);
}

void InputManager::ProcessEvent(SDL_Event event)
{
	if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN)
		this->ProcessKeyEvent(event);

	else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
		this->ProcessMouseButtonEvent(event);

	else if (event.type == SDL_MOUSEMOTION)
		this->ProcessMouseMotionEvent(event);

}

void InputManager::Update()
{
	mouseDelta = Vector2(0, 0);
	wasMouseDownLeft = leftMouseDown;
	wasMouseDownRight = rightMouseDown;
}

void InputManager::ProcessMouseMotionEvent(SDL_Event e)
{
	mousePosition = Vector2(e.motion.x, e.motion.y);
	mouseDelta = Vector2(e.motion.xrel, e.motion.yrel);
}

void InputManager::ProcessMouseButtonEvent(SDL_Event e)
{
	//Otherwise set mouse button state
	if (e.button.button == SDL_BUTTON_LEFT)
		leftMouseDown = (e.type == SDL_MOUSEBUTTONDOWN);

	else if (e.button.button == SDL_BUTTON_RIGHT)
		rightMouseDown = (e.type == SDL_MOUSEBUTTONDOWN);
}
