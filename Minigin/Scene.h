#pragma once
#include "SceneManager.h"
#include "BoxColliders.h"
#include "EventQueue.h"

namespace dae
{
	class GameObject;
	class Scene : public Subject
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);

		void Init(InputHandler& input);
		void Update(float deltaTime);
		void Render() const;

		//void SwitchActive();
		void AddBoxColliders(const std::shared_ptr<BoxColliders>& boxColliders);

		//~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		//std::shared_ptr<GameObject> GetGOById(std::string id) const;
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector <std::shared_ptr<GameObject>> m_Objects{};

		std::shared_ptr<Subject> m_pSubject;
		std::shared_ptr<EventQueue<Command::inputEvent>> m_pInputEvents;
		bool m_Playing;

		static unsigned int m_IdCounter; 
	};

}
