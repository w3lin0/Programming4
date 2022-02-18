#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Font.h"

namespace dae
{
	class Texture2D;
	class TextObject;

	// todo: this should become final.
	class GameObject final : public SceneObject
	{
	public:
		void Update(float deltaTime) override;
		void Render() const override;

		template <typename T> T* AddComponent(T* component);
		template <typename T> T* GetComponent(T* component) const;
		template <typename T> void RemoveComponent(T* component);

		void SetParent(GameObject* parent);
		GameObject* GetParent() const;

		size_t GetChildCount() const;
		GameObject* GetChildAt(int index) const;
		void RemoveChild(int index);
		void AddChild(GameObject* go);

		//virtual void SetTexture(const std::string& filename) const = 0;
		void SetPosition(float x, float y);

		GameObject(float posX, float posY, std::string fileNameTex = "", std::string text = "", const std::shared_ptr<Font>& font = nullptr);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		GameObject* m_Parent = nullptr;
		std::vector<GameObject*> m_Children;

		TextObject* m_TextComponent = nullptr;
		Texture2D* m_SpriteComponent = nullptr;
	};
}
