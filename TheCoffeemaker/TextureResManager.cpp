#include "TextureResManager.h"
#include <string>

#include <TheCoffeeMaker/Console.h>

namespace CMaker {
	/* PATHS */
	const std::map< CMaker::Texture, std::string > TextureResManager::paths = {
		{ Texture::SMALL_LOGO, "textures/small_logo.png" },
		{ Texture::FOCZKA_ENGINE_LOGO, "textures/foczka_engine.png" },
		{ Texture::TECH_LOGOS, "textures/tech_logos.png" },
		{ Texture::BUBUS_FACE, "textures/bubus_face.png" },
		
		{ Texture::NONE, "textures/none.png" }
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
		std::string lPath;

		auto it = paths.find(_texture);
		if (it != paths.end()) {
			lPath = it->second;
		}
		else {
			throw new std::exception("Path to this texture not found.");
		}

		// Load and insert resource
		std::unique_ptr< sf::Texture > tmpTexture( new sf::Texture() );
		if (!tmpTexture->loadFromFile(lPath)) {
			std::string msg = "Texture not found in given path: " + lPath;
			throw new std::exception(msg.c_str());
		}

		// Process texture
		tmpTexture->setSmooth(true);

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