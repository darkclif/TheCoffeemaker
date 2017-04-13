#include "ResourceManager.h"

namespace CMaker {
	/*
		Resource access
	*/
	sf::Font & ResourceManager::getResource(CMaker::Font _font)
	{
		return fontManager.getFont(_font);
	}

	sf::Texture & ResourceManager::getResource(CMaker::Texture _text)
	{
		return textManager.getTexture(_text);
	}

	/*
	sf::Font & ResourceManager::getResource(CMaker::Font _font)
	{
		return fontManager.getFont(_font);
	}
	*/

	/*
		CONSTRUCTOR / DESTRUCTOR
	*/
	ResourceManager::ResourceManager()
	{
	}

	ResourceManager::~ResourceManager()
	{
	}

}