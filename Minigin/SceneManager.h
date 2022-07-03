#pragma once
#include "Singleton.h"
#include "InputHandler.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Init(InputHandler& input);
		void Update(float deltaTime);
		void Render();

		//~SceneManager();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
