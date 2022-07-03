#pragma once

class BaseComponent {
public:
	BaseComponent() {};

	virtual void Update(float elapsedSec) = 0;
	virtual void Render(glm::vec3 pos) const = 0;

	virtual ~BaseComponent() = default;
};