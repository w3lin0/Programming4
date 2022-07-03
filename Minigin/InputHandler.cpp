#include "MiniginPCH.h"
#include "InputHandler.h"
#include "InputManager.h"

InputHandler::InputHandler(int controllerIndex)
	:m_InputManager{controllerIndex}
{
}

bool InputHandler::handleInput()
{
	bool result = m_InputManager.ProcessInput();

	if (m_InputManager.IsDownThisFrame(dae::ControllerButton::ButtonX) && buttonX_ != nullptr) buttonX_->execute();
	else if (m_InputManager.IsUpThisFrame(dae::ControllerButton::ButtonY) && buttonY_ != nullptr) buttonY_->execute();
	else if (m_InputManager.IsPressed(dae::ControllerButton::ButtonA) && buttonA_ != nullptr) buttonA_->execute();
	else if (m_InputManager.IsPressed(dae::ControllerButton::ButtonB) && buttonB_ != nullptr) buttonB_->execute();
	else if (m_InputManager.IsPressed(dae::ControllerButton::ArrowLeft) && buttonArrowLeft_ != nullptr) buttonArrowLeft_->execute();
	else if (m_InputManager.IsPressed(dae::ControllerButton::ArrowRight) && buttonArrowRight_ != nullptr) buttonArrowRight_->execute();

	return result;
}

void InputHandler::bindCommand(dae::ControllerButton button, Command* command)
{
	switch (button)
	{
	case dae::ControllerButton::ButtonA:
		buttonA_.reset(command);
		break;
	case dae::ControllerButton::ButtonB:
		buttonB_.reset(command);
		break;
	case dae::ControllerButton::ButtonX:
		buttonX_.reset(command);
		break;
	case dae::ControllerButton::ButtonY:
		buttonY_.reset(command);
		break;
	case dae::ControllerButton::ArrowUp:
		buttonArrowUp_.reset(command);
		break;
	case dae::ControllerButton::ArrowDown:
		buttonArrowDown_.reset(command);
		break;
	case dae::ControllerButton::ArrowLeft:
		buttonArrowLeft_.reset(command);
		break;
	case dae::ControllerButton::ArrowRight:
		buttonArrowRight_.reset(command);
		break;
	case dae::ControllerButton::Start:
		buttonStart_.reset(command);
		break;
	case dae::ControllerButton::Back:
		buttonBack_.reset(command);
		break;
	case dae::ControllerButton::ThumbLeft:
		buttonThumbLeft_.reset(command);
		break;
	case dae::ControllerButton::ThumbRight:
		buttonThumbRight_.reset(command);
		break;
	case dae::ControllerButton::ShoulderLeft:
		buttonShoulderLeft_.reset(command);
		break;
	case dae::ControllerButton::ShoulderRight:
		buttonShoulderRight_.reset(command);
		break;
	default:
		break;
	}
}
