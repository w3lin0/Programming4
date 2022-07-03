#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "GameObject.h"

class CharacterComponent : public BaseComponent
{
	enum class States {
		walkFreely,
		onStairs
	};
public:
	CharacterComponent();

	void Update(float elapsedSec) override;
	void Render(glm::vec3 pos) const override;

	void Physics(dae::GameObject& gameObject);

	void MoveLeft();
	void MoveRight();
	void MoveUp(){};
	void MoveDown(){};

private:
	std::shared_ptr<dae::Texture2D> m_pTexture;
	glm::vec3 m_Position;

	bool m_moveRight{ false };
	bool m_moveLeft{ false };

	States m_characterStates;
};

