#pragma once
#include <SFML/Graphics.hpp>

#include <TheCoffeeMaker/FontResManager.h>
#include <TheCoffeeMaker/TextureResManager.h>

namespace CMaker {

	#define ResourceMgr ResourceManager::getInstance()

	class ResourceManager
	{
	public:
		// Singleton
		static ResourceManager& getInstance() {
			static ResourceManager instance;
			return instance;
		}

		// Resources handlers
		sf::Font&		getResource(CMaker::Font _font);
		sf::Texture&	getResource(CMaker::Texture _text);

		ResourceManager();
		~ResourceManager();

	private:
		FontResManager fontManager;
		TextureResManager textManager;

		// Singleton
		ResourceManager(const ResourceManager &) = delete;
		void operator=(ResourceManager const & ) = delete;
	};

}