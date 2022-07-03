#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "TextObject.h"
#include "Renderer.h"

dae::TextObject::TextObject(const std::string& text, const std::shared_ptr<Font>& font) 
	: m_NeedsUpdate(true), m_Text(text), m_Font(font), m_TextTexture(nullptr), m_Color{255,255,255}
{ }

dae::TextObject::TextObject(TextObject&& other) noexcept
	:m_NeedsUpdate(other.m_NeedsUpdate), m_Text(other.m_Text), m_Font(other.m_Font), m_TextTexture(other.m_TextTexture), m_Color(other.m_Color)
{
}

void dae::TextObject::Update(float)
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr) 
		{
			OutputDebugString((std::string("Render text failed: ") + SDL_GetError() + "\n").c_str());
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextObject::Render(glm::vec3 pos) const
{
	if (m_TextTexture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextObject::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextObject::SetColor(SDL_Color color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}


