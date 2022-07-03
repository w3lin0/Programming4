#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextObject.h"
#include "Texture2D.h"
#include "LivesComponent.h"
#include "CharacterComponent.h"

dae::GameObject::GameObject(std::string id, float posX, float posY)
	:m_Id{id}
	,m_Time{0.0f}
	,m_FrameCount{0}
	,m_pTransform{std::make_shared<Transform>()}
{
	m_pTransform->SetPosition(posX, posY, 0.0f);
}

void dae::GameObject::Update(float deltaTime)
{
	if(GetComponent<CharacterComponent>() != nullptr)
		GetComponent<CharacterComponent>()->Physics(*this);

	for (auto component : m_Components) {
		component->Update(deltaTime);
	}
}
void dae::GameObject::Render() const
{
	for (auto component : m_Components) {
		component->Render(m_pTransform->GetPosition());
	}
}


void dae::GameObject::SetParent(std::shared_ptr<GameObject> parent)
{
	m_Parent = parent;
	if (m_Parent->GetChildById(m_Id) == nullptr) {
		parent->AddChild(std::shared_ptr<GameObject>(this));
	}
}
std::shared_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
	return m_Parent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_Children.size();
}
std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(size_t index) const
{
	return m_Children.at(index);
}
std::shared_ptr<dae::GameObject> dae::GameObject::GetChildById(std::string id)
{
	for (const auto& object : m_Children)
	{
		if (object->GetId() == id) {
			return object;
		}
	}
	return nullptr;
}
void dae::GameObject::RemoveChild(size_t index)
{
	GetChildAt(index)->SetParent(nullptr);
	if (index < m_Children.size() && index >= 0) {
		for (size_t i{ index + 1 }; i < m_Children.size(); ++i) {
			m_Children[i - 1] = m_Children[i];
		}
		m_Children.pop_back();
	}
}
//void dae::GameObject::RemoveChildById(std::string id)
//{
//
//}
void dae::GameObject::AddChild(std::shared_ptr<GameObject> go)
{
	bool alreadyChild{ false };
	for (auto& child : m_Children) {
		if (child == go) {
			alreadyChild = true;
		}
	}
	if (!alreadyChild) {
		m_Children.push_back(go);
		/*if (go->GetParent() != std::shared_ptr<GameObject>(this)) {
			go->SetParent(std::shared_ptr<GameObject>(this));
		}*/
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	glm::vec3 deltaPosition = glm::vec3(x, y, 0.0f) - m_pTransform->GetPosition();
	
	for (auto& child : m_Children) {
		child->SetPosition(child->GetPosition().x + deltaPosition.x, child->GetPosition().y + deltaPosition.y);
	}

	m_pTransform->SetPosition(x, y, 0.0f);
}
glm::vec3 dae::GameObject::GetPosition()
{
	return m_pTransform->GetPosition();
}

std::string dae::GameObject::GetId()
{
	return m_Id;
}
