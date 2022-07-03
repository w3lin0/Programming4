#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#include <iostream>
#include <thread>
#include "MiniginPCH.h"
#include "InputManager.h"

#pragma comment(lib, "xinput.lib")

class dae::InputManager::ControllerImpl {
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	int m_ControllerIndex;
public:
	ControllerImpl(int controllerIndex)
		:m_ControllerIndex{ controllerIndex }
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	}

	bool Update() {
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(0, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return false;
			}
			if (e.type == SDL_KEYDOWN) {
				/*std::cout << "-1 live\n";*/
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
					
			}
		}

		return true;
	}

	bool IsUp(unsigned int button) { return m_ButtonsReleasedThisFrame & button; }
	bool IsDown(unsigned int button) { return m_ButtonsPressedThisFrame & button; }
	bool IsPressed(unsigned int button) { return m_CurrentState.Gamepad.wButtons & button; }
};

dae::InputManager::InputManager(int controllerIndex)
{
	pImpl = new ControllerImpl(controllerIndex);
}

dae::InputManager::~InputManager()
{
	delete pImpl;
	pImpl = nullptr;
}

bool dae::InputManager::ProcessInput()
{
	return pImpl->Update();
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	return pImpl->IsPressed(unsigned int(button));
}

bool dae::InputManager::IsDownThisFrame(ControllerButton button) const
{
	return pImpl->IsDown(unsigned int(button));
}

bool dae::InputManager::IsUpThisFrame(ControllerButton button) const
{
	return pImpl->IsUp(unsigned int(button));
}

