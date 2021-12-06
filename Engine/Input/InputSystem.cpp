#include "InputSystem.h"
#include <iostream>
#include <algorithm>

namespace nc
{
	void InputSystem::Startup()
	{
		// set size of keyboard state
		const Uint8* keyboardStateSDL = SDL_GetKeyboardState(&numKeys);

		keyboardState.resize(numKeys);
		std::copy(keyboardStateSDL, keyboardStateSDL + numKeys - 1, keyboardState.begin());

		prevKeyboardState = keyboardState;

		// set initial mouse position
		int x, y;
		Uint32 buttons = SDL_GetMouseState(&x, &y);
		mousePosition = glm::vec2{ x , y };
		prevMousePosition = mousePosition;

	}

	void InputSystem::Shutdown()
	{

	}

	void InputSystem::Update(float dt)
	{
		prevKeyboardState = keyboardState;

		const Uint8* keyboardStateSDL = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardStateSDL, keyboardStateSDL + numKeys, keyboardState.begin());

		prevMouseButtonState = mouseButtonState;
		prevMousePosition = mousePosition;

		int x, y;
		Uint32 buttons = SDL_GetMouseState(&x, &y);
		mousePosition =  { x, y };
		mouseButtonState[0] = buttons & SDL_BUTTON_LMASK;
		mouseButtonState[1] = buttons & SDL_BUTTON_MMASK;
		mouseButtonState[2] = buttons & SDL_BUTTON_RMASK;
		mouseRelative = mousePosition - prevMousePosition;
	}

	InputSystem::eKeyState InputSystem::GetKeyState(int id)
	{
		eKeyState state = eKeyState::Idle;
		bool keyDown = IsKeyDown(id);
		bool prevKeydown = IsPreviousKeyDown(id);

		if (keyDown)
		{
			state = (prevKeydown) ? state = eKeyState::Held : state = eKeyState::Pressed;
		}
		else
		{
			state = (prevKeydown) ? state = eKeyState::Idle : state = eKeyState::Release;
		}

		return state;
	}

	InputSystem::eKeyState InputSystem::GetButtonState(int id)
	{
		eKeyState state = eKeyState::Idle;
		bool buttonDown = IsButtonDown(id);
		bool prevButtondown = IsPreviousButtonDown(id);

		if (buttonDown)
		{
			state = (prevButtondown) ? state = eKeyState::Held : state = eKeyState::Pressed;
		}
		else
		{
			state = (prevButtondown) ? state = eKeyState::Idle : state = eKeyState::Release;
		}

		return state;
	}
}