#pragma once
#include "Font.h"
#include "Texture2D.h"

namespace dae
{
	class TextObject : public BaseComponent
	{
	public:
		TextObject(const std::string& text, const std::shared_ptr<Font>& font);

		void Update(float elapsedSec) override;
		void Render(glm::vec3 pos) const override;

		void SetText(const std::string& text);
		void SetColor(SDL_Color color);

		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) noexcept;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
		SDL_Color m_Color;
	};
}
