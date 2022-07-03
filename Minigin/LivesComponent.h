#pragma once
#include "GameObject.h"
#include "Subject.h"
#include "TextObject.h"
#include "Font.h"

class LivesComponent : public BaseComponent
{
public:
	LivesComponent(int totalLives, const std::shared_ptr<dae::Font>& font);

	void Update(float elapsedSec) override;
	void Render(glm::vec3 position) const override;

	void AddLive();
	void RemoveLive();

	bool IsDead() { return m_Dead; }

private:
	std::shared_ptr<dae::TextObject> m_pTextObject;
	int m_Lives;
	bool m_Dead;
};

