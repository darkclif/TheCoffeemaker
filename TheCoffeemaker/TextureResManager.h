#pragma once
#include <string>
#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

namespace CMaker {
	
	/* TEXTURES */
	enum class Texture {
		NONE, /* Blank texture */

		SMALL_LOGO,
		FOCZKA_ENGINE_LOGO,
		TECH_LOGOS
	};

	/* Textures managment */
	class TextureResManager 
	{
	public:
		sf::Texture&					getTexture(CMaker::Texture _texture);

										TextureResManager();
										~TextureResManager();

	private:
		void							loadTexture(CMaker::Texture _texture);

		std::map< CMaker::Texture, std::unique_ptr< sf::Texture > >		resources;
		static const std::map< CMaker::Texture, std::string >			paths;
	};

}