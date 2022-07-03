#pragma once
#include "BaseComponent.h"
#include "TextObject.h"
#include "Font.h"

class FPSComponent : public BaseComponent
{
public:
	FPSComponent(const std::shared_ptr<dae::Font>& font);

	void Update(float elapsedSec) override;
	void Render(glm::vec3 pos) const override;

	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) = delete;

private:
	std::shared_ptr<dae::TextObject> m_pTextObject;
	float m_Time;
	int m_FrameCount;
};

