#pragma once
#include "../BurgerTime/Command.h"
#include "InputManager.h"

class InputHandler
{
public:
	InputHandler(int controllerIndex);

	bool handleInput();

	// Methods to bind commands...
	void bindCommand(dae::ControllerButton button, Command* command);

private:
	dae::InputManager m_InputManager;

	std::unique_ptr<Command> buttonX_ = nullptr;
	std::unique_ptr<Command> buttonY_ = nullptr;
	std::unique_ptr<Command> buttonA_ = nullptr;
	std::unique_ptr<Command> buttonB_ = nullptr;
	std::unique_ptr<Command> buttonArrowLeft_ = nullptr;
	std::unique_ptr<Command> buttonArrowRight_ = nullptr;
	std::unique_ptr<Command> buttonArrowUp_ = nullptr;
	std::unique_ptr<Command> buttonArrowDown_ = nullptr;
	std::unique_ptr<Command> buttonStart_ = nullptr;
	std::unique_ptr<Command> buttonBack_ = nullptr;
	std::unique_ptr<Command> buttonThumbLeft_ = nullptr;
	std::unique_ptr<Command> buttonThumbRight_ = nullptr;
	std::unique_ptr<Command> buttonShoulderLeft_ = nullptr;
	std::unique_ptr<Command> buttonShoulderRight_ = nullptr;
};

