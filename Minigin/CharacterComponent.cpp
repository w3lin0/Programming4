#include "MiniginPCH.h"
#include "CharacterComponent.h"
#include "BoxColliders.h"

CharacterComponent::CharacterComponent()
	:m_pTexture{std::make_shared<dae::Texture2D>("test.png")}
	,m_characterStates{States::walkFreely}
	,m_Position{}
{
}

void CharacterComponent::Update(float)
{
	switch (m_characterStates)
	{
	case States::walkFreely:
		break;
	case States::onStairs:
		break;
	default:
		break;
	}
}

void CharacterComponent::Render(glm::vec3 pos) const
{
	m_pTexture->Render(pos);
}

void CharacterComponent::Physics(dae::GameObject& gameObject)
{
	m_Position = gameObject.GetPosition();
	if (m_moveRight) {
		gameObject.SetPosition(gameObject.GetPosition().x + 1, gameObject.GetPosition().y);
		m_moveRight = false;
	}
	if (m_moveLeft) {
		gameObject.SetPosition(gameObject.GetPosition().x - 1, gameObject.GetPosition().y);
		m_moveLeft = false;
	}
	if (!gameObject.GetComponent<BoxColliders>()->Hit(gameObject.GetPosition()) && gameObject.GetPosition().y < 435.0f) {
		gameObject.SetPosition(gameObject.GetPosition().x, gameObject.GetPosition().y + 1.0f);
	}
}

void CharacterComponent::MoveLeft()
{
	if (!m_moveLeft && m_characterStates == States::walkFreely) {
		m_moveLeft = true;
	}
}
void CharacterComponent::MoveRight()
{
	if (!m_moveRight && m_characterStates == States::walkFreely) {
		m_moveRight = true;
	}
}
