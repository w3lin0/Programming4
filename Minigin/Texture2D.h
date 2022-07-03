#pragma once
#include "BaseComponent.h"

struct SDL_Texture;
namespace dae
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D : public BaseComponent
	{
	public:
		SDL_Texture* GetSDLTexture() const;

		void Render(glm::vec3 pos) const override;

		Texture2D(std::string fileName);
		Texture2D(SDL_Texture* texture);

		void SetTexture2D(std::string fileName);
		void SetTexture2D(SDL_Texture* texture);

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

		void Update(float) override {};
		//~Texture2D() override {};
	private:
		std::shared_ptr<Texture2D> m_Texture;
		SDL_Texture* m_pSDLTexture;
	};
}
