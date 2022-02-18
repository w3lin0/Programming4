#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextObject.h"
#include "Texture2D.h"

dae::GameObject::GameObject(float posX, float posY, std::string fileNameTex, std::string text, const std::shared_ptr<Font>& font)
{
	m_Transform.SetPosition(posX, posY, 0.0f);
	if (fileNameTex != "") {
		m_SpriteComponent = new Texture2D(fileNameTex);
	}
	if (text != "" && font != nullptr) {
		m_TextComponent = new TextObject(text, font);
	}
}

dae::GameObject::~GameObject() {
	for (int i{}; i < m_Children.size(); ++i) {
		delete m_Children.at(i);
		m_Children.at(i) = nullptr;
	}
	delete m_TextComponent;
	m_TextComponent = nullptr;
	delete m_SpriteComponent;
	m_SpriteComponent = nullptr;
	delete m_Parent;
	m_Parent = nullptr;
}

void dae::GameObject::Update(float deltaTime)
{
	deltaTime;
}

void dae::GameObject::Render() const
{
	if (m_TextComponent != nullptr) {
		m_TextComponent->Render(m_Transform.GetPosition());
	}
	if (m_SpriteComponent != nullptr) {
		m_SpriteComponent->Render(m_Transform.GetPosition());
	}
}

template<typename T>
T* dae::GameObject::AddComponent(T* component)
{
	switch (T)
	{
	case TextObject:
		m_TextComponent = component;
		return m_TextComponent;
	case Texture2D:
		m_SpriteComponent = component;
		return m_SpriteComponent;
	default:
		std::cout << "Failed to add component: " << T << std::endl;
		return nullptr;
	}
}

template<typename T>
T* dae::GameObject::GetComponent(T* component) const
{
	switch (T)
	{
	case TextObject:
		if (m_TextComponent != nullptr) {
			return m_TextComponent;
		}
	case Texture2D:
		if (m_SpriteComponent != nullptr) {
			return m_SpriteComponent;
		}
	default:
		std::cout << "Failed to get component: " << T << std::endl;
		return nullptr;
	}
}

template<typename T>
void dae::GameObject::RemoveComponent(T* component)
{
	switch (T)
	{
	case TextObject:
		delete m_TextComponent;
		m_TextComponent = nullptr;
		break;
	case Texture2D:
		delete m_SpriteComponent;
		m_SpriteComponent = nullptr;
		break;
	default:
		break;
	}
}

void dae::GameObject::SetParent(GameObject* parent)
{
	m_Parent = parent;
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_Parent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_Children.size();
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	return m_Children.at(index);
}

void dae::GameObject::RemoveChild(int index)
{
	if (index < m_Children.size() && index >= 0) {
		for (int i{ index + 1 }; i < m_Children.size(); ++i) {
			m_Children[i - 1] = m_Children[i];
		}
		m_Children.pop_back();
	}
}

void dae::GameObject::AddChild(GameObject* go)
{
	m_Children.push_back(go);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
