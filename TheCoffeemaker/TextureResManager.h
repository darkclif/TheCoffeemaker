#pragma once
#include <string>
#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

namespace CMaker {
	
	/* TEXTURES */
	enum class Texture {
		/* Blank texture */
		NONE

		/* Logos */
		,SMALL_LOGO 
		,FOCZKA_ENGINE_LOGO
		,TECH_LOGOS
		,BUBUS_FACE

		/* Game entities */
		,TABLE
		,BACKGROUND
		,COFFEE_SMALL
		, COFFEE_BIG
		, COFFEE_SMALL_STACK
		, COFFEE_BIG_STACK
		, HEAT_BAR
		, BIN
		, COFFEE_MACHINE
	};

	/* Textures managment */
	class TextureResManager 
	{
	public:
		sf::Texture&					getTexture(CMaker::Texture _texture);

										TextureResManager();
										~TextureResManager();

	private:
		struct TextureInfo {
			std::string path;
			bool		smooth;
		};

		void							loadTexture(CMaker::Texture _texture);

		std::map< CMaker::Texture, std::unique_ptr< sf::Texture > >		resources;
		static const std::map< CMaker::Texture, TextureInfo >			res_info;
	};

}