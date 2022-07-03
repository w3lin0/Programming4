#include "MiniginPCH.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "Texture2D.h"
#include "LivesComponent.h"
#include "../BurgerTime/InGameSystem.h"
#include "CharacterComponent.h"
#include "LeaderbordComp.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name), m_Playing(true), m_pInputEvents{ std::make_shared<EventQueue<Command::inputEvent>>(30) } {}

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

//std::shared_ptr<dae::GameObject> dae::Scene::GetGOById(std::string id) const
//{
//	for (const auto& object : m_Objects)
//	{
//		if (object->GetId() == id) {
//			return object;
//		}
//	}
//	return nullptr;
//}

//void dae::Scene::SwitchActive()
//{
//	if (m_Playing) {
//		m_Playing = false;
//	}
//	else { m_Playing = true; }
//}