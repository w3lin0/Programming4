#pragma once
#include "BaseComponent.h"

class BoxColliders : public BaseComponent
{
public:
	void Update(float elapsedSec) override;
	void Render(glm::vec3 pos) const override;

	bool Hit(glm::vec3 pos);

	void AddBoxCollider(std::string id, float topLeftX, float topLeftY, float width, float height = 1.0f);
	void RemoveBoxCollider(std::string id);
	void RemoveBoxCollider(size_t index);

private:
	struct boxCollider {
		std::string id;
		float x;
		float y;
		float width;
		float height;
	};
	std::vector<std::shared_ptr<boxCollider>> m_pBoxColliders;
};

