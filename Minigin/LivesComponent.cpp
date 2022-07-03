#include "MiniginPCH.h"
#include "LivesComponent.h"

LivesComponent::LivesComponent(int totalLives, const std::shared_ptr<dae::Font>& font)
	:m_Lives{totalLives}
	,m_pTextObject{ std::make_shared<dae::TextObject>("Lives: " + std::to_string(totalLives), font)}
	,m_Dead{false}
{
	m_pTextObject->SetColor({ 255,0,0 });
}

void LivesComponent::Update(float elapsedSec)
{
	m_pTextObject->Update(elapsedSec);
}

void LivesComponent::Render(glm::vec3) const
{
	m_pTextObject->Render({ 450.0f, 5.0f, 0.0f });
}

void LivesComponent::AddLive()
{
	++m_Lives;
	m_pTextObject->SetText("Lives: " + std::to_string(m_Lives));
}

void LivesComponent::RemoveLive()
{
	if (m_Lives <= 1) {
		m_pTextObject->SetText("Died!");
		m_Dead = true;
	}
	else {
		--m_Lives;
		m_pTextObject->SetText("Lives: " + std::to_string(m_Lives));
	}
}
