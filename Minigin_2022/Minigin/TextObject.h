#pragma once
#include "GameObject.h"
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextObject final
	{
	public:
		void Update(float deltaTime);
		void Render(glm::vec3 pos) const;

		void SetText(const std::string& text);

		explicit TextObject(const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
	};
}
