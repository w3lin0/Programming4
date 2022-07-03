#include "MiniginPCH.h"
#include "BoxColliders.h"

void BoxColliders::Update(float)
{
}
void BoxColliders::Render(glm::vec3) const
{
}

bool BoxColliders::Hit(glm::vec3 pos)
{
	for (auto boxCollider : m_pBoxColliders) {
		if (pos.y >= boxCollider->y - 45.0f && pos.y < boxCollider->y
			&& pos.x >= boxCollider->x && pos.x <= boxCollider->x+boxCollider->width) {
			return true;
		}
	}
	return false;
}

void BoxColliders::AddBoxCollider(std::string id, float topLeftX, float topLeftY, float width, float height)
{
	m_pBoxColliders.push_back(std::make_shared<boxCollider>(id, topLeftX, topLeftY, width, height));
}
void BoxColliders::RemoveBoxCollider(std::string id)
{
	size_t index{ 0 };
	for(auto boxCollider : m_pBoxColliders) {
		if (boxCollider->id == id)
			break;
		++index;
	}

	if (index + 1 == m_pBoxColliders.size()) {
		m_pBoxColliders.pop_back();
	}
	else if (index + 1 > m_pBoxColliders.size()) {
		std::cout << "Error: To big of an index!";
		return;
	}
	else {
		for (size_t i{ index + 1 }; i < m_pBoxColliders.size(); ++i) {
			m_pBoxColliders[i - 1] = m_pBoxColliders[i];
		}
		m_pBoxColliders.pop_back();
	}
}
void BoxColliders::RemoveBoxCollider(size_t index)
{
	if (index + 1 == m_pBoxColliders.size()) {
		m_pBoxColliders.pop_back();
	}
	else if (index + 1 > m_pBoxColliders.size()) {
		std::cout << "Error: To big of an index!";
		return;
	}
	else {
		for (size_t i{ index + 1 }; i < m_pBoxColliders.size(); ++i) {
			m_pBoxColliders[i - 1] = m_pBoxColliders[i];
		}
		m_pBoxColliders.pop_back();
	}
}
