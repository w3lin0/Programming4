#include "MiniginPCH.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::Texture2D::~Texture2D()
{
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_SDLTexture;
}

void dae::Texture2D::Render(glm::vec3 pos) const
{
	if (m_Texture != nullptr) {
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

dae::Texture2D::Texture2D(std::string fileName)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(fileName);
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_SDLTexture = texture;
}
