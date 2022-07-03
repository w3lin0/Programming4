#include "MiniginPCH.h"
#include "FPSComponent.h"

FPSComponent::FPSComponent(const std::shared_ptr<dae::Font>& font)
	:m_Time{ 0.0f }
	,m_FrameCount{ 0 }
	,m_pTextObject{ std::make_shared<dae::TextObject>(" Fps", font) }
{
	m_pTextObject->SetColor(SDL_Color{ 0,255,0 });
}

void FPSComponent::Update(float elapsedSec)
{
	//Update m_Time
	if (m_Time < 1.0f) {
		m_FrameCount++;
		m_Time += elapsedSec;
	}

	if (m_Time >= 1.0f) {
		m_pTextObject->SetText(std::to_string(m_FrameCount) + " Fps");
	}
	m_pTextObject->Update(elapsedSec);
	
	//reset m_Time
	if (m_Time >= 1.0f) {
		m_FrameCount = 0;
		m_Time = 0.0f;
	}
}

void FPSComponent::Render(glm::vec3 pos) const
{
	m_pTextObject->Render(pos);
}
