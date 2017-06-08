#include "TextureResManager.h"
#include <string>

#include <TheCoffeeMaker/Console.h>

namespace CMaker {
	/* PATHS */
	const std::map< CMaker::Texture, TextureResManager::TextureInfo > TextureResManager::res_info = {
		/* Game entities */
		{ Texture::TABLE, { "textures/table.png", false } },
		{ Texture::BACKGROUND, {"textures/background.png", true} },

		{ Texture::COFFEE_SMALL, { "textures/coffee_small.png", false } },
		{ Texture::COFFEE_BIG, { "textures/coffee_big.png", false } },
		{ Texture::COFFEE_SMALL_STACK,{ "textures/coffee_small_stack.png", false } },
		{ Texture::COFFEE_BIG_STACK,{ "textures/coffee_big_stack.png", false } },
		{ Texture::HEAT_BAR,{ "textures/heat_bars.png", false } },
		
		{ Texture::BIN,{ "textures/bin.png", false } },
		{ Texture::CUSTOMERS,{ "textures/customers.png", false } },

		{ Texture::COFFEE_MACHINE,{ "textures/coffee_machine.png", false } },

		/* Logos */
		{ Texture::SMALL_LOGO, { "textures/small_logo.png", true } },
		{ Texture::FOCZKA_ENGINE_LOGO, { "textures/foczka_engine.png", true } },
		{ Texture::TECH_LOGOS, { "textures/tech_logos.png", true } },
		{ Texture::BUBUS_FACE, { "textures/bubus_face.png", true } },
		
		/* Special */
		{ Texture::NONE, { "textures/none.png", true } }
	};

	sf::Texture & TextureResManager::getTexture(CMaker::Texture _tex)
	{
		auto it = resources.find(_tex);
		if (it != resources.end()) {
			return *(it->second);
		}
		else {
			try {
				this->loadTexture(_tex);
				return getTexture(_tex);
			}
			catch (std::exception e) {
				C_DEBUG << S_ERROR << "Exception when loading texture: " << e.what() << std::endl;
				C_DEBUG << S_ERROR << "Texture::NONE loaded instead." << std::endl;
				
				if (_tex != Texture::NONE) {
					return getTexture(Texture::NONE);
				}
				else {
					throw std::exception("Fatal: Cannot load Texture::NONE texture.");
				}
			}
		}
	}

	void TextureResManager::loadTexture(CMaker::Texture _texture)
	{
		// Get path to this resource
		TextureInfo lTexInfo;

		auto it = res_info.find(_texture);
		if (it != res_info.end()) {
			lTexInfo = it->second;
		}
		else {
			throw new std::exception("Path to this texture not found.");
		}

		// Load and insert resource
		std::unique_ptr< sf::Texture > tmpTexture( new sf::Texture() );
		if (!tmpTexture->loadFromFile(lTexInfo.path)) {
			std::string msg = "Texture not found in given path: " + lTexInfo.path;
			throw new std::exception(msg.c_str());
		}

		// Process texture
		tmpTexture->setSmooth(lTexInfo.smooth);

		resources.insert(std::make_pair(_texture, std::move(tmpTexture)));
	}

	/*
		CONSTRUCTOR / DESTRUCTOR
	*/
	TextureResManager::TextureResManager()
	{

	}

	TextureResManager::~TextureResManager()
	{

	}
}