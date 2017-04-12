#include "ResourceManager.h"

namespace CMaker {
	/*
		Resource access
	*/
	sf::Font & ResourceManager::getResource(CMaker::Font _font)
	{
		return fontManager.getFont(_font);
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