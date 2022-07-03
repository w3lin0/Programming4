#pragma once
#include "Transform.h"
#include "Font.h"
//#include "BaseComponent.h"
#include "FPSComponent.h"
#include "TextObject.h"
#include "Texture2D.h"

namespace dae
{
	//class Texture2D;
	//class TextObject;

	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void Render() const;

		template <typename T> std::shared_ptr<BaseComponent> AddComponent(std::shared_ptr<T> component) {
			m_Components.push_back(component);
			return m_Components.at(m_Components.size() - 1);
		};
		template <typename T> std::shared_ptr<T> GetComponent() const {
			for (auto component : m_Components) {
				std::shared_ptr<T> castedComp{ dynamic_pointer_cast<T>(component) };
				if (castedComp)
					return castedComp;
			}
			return nullptr;
		};
		template <typename T> void RemoveComponent() {
			int index{ 0 };
			if (m_Components.size() > 0) {
				/*for (auto component : m_Components) {
					if (typeid(T) == typeid(component)) {
						return;
					}
					index++;
				}*/
				for (auto component : m_Components) {
					std::shared_ptr<T> castedComp{ dynamic_pointer_cast<T>(component) };
					if (castedComp) {
						break;
					}
					index++;
				}
				if (index + 1 == m_Components.size()) {
					m_Components.pop_back();
				}
				else if (index + 1 > m_Components.size()) {
					return;
				}
				else {
					for (int i{ index + 1 }; i < m_Components.size(); ++i) {
						m_Components[i - 1] = m_Components[i];
					}
					m_Components.pop_back();
				}
			}
		};



		void SetParent(std::shared_ptr<GameObject> parent);//child en oude parent aanpassen
		std::shared_ptr<GameObject> GetParent() const;

		size_t GetChildCount() const;
		std::shared_ptr<GameObject> GetChildAt(size_t index) const;
		std::shared_ptr<GameObject> GetChildById(std::string id);
		void RemoveChild(size_t index);
		//void RemoveChildById(std::string id);
		void AddChild(std::shared_ptr<GameObject> go);

		void SetPosition(float x, float y);
		glm::vec3 GetPosition();
		std::string GetId();

		//~GameObject();
		GameObject(std::string id, float posX, float posY);
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		//size_t GetChildIndexById(std::string)

		std::string m_Id;
		std::shared_ptr<Transform> m_pTransform;
		std::shared_ptr<GameObject> m_Parent = nullptr;
		std::vector<std::shared_ptr<GameObject>> m_Children;
		float m_Time;
		int m_FrameCount;

		std::vector<std::shared_ptr<BaseComponent>> m_Components;
	};
}
