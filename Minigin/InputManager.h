#pragma once
#include <windows.h>
#include <XInput.h>
#include "Singleton.h"

namespace dae
{
	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
		ArrowUp = 0x0001,
		ArrowDown = 0x0002,
		ArrowLeft = 0x0004,
		ArrowRight = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		ThumbLeft = 0x0040,
		ThumbRight = 0x0080,
		ShoulderLeft = 0x0100,
		ShoulderRight = 0x0200
	};

	class InputManager final
	{
		class ControllerImpl;
		ControllerImpl* pImpl;
	public:
		InputManager(int controllerIndex);
		~InputManager();

		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		bool IsDownThisFrame(ControllerButton button) const;
		bool IsUpThisFrame(ControllerButton button) const;
	};

}
