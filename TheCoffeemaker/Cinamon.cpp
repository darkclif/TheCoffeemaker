#include "Cinamon.h"
#include <TheCoffeeMaker/Transforms.h>
#include <TheCoffeeMaker/ResourceManager.h>

namespace CMaker {

	Cinamon::Cinamon(sf::Vector2f _pos):
		SimpleAnimation(CMaker::Texture::NONE, _pos)
	{
		animationEngine.addAnimation(1);
		animationEngine.addTransform(1, new transFade(sf::Uint8(0), sf::seconds(2)));
		animationEngine.addTransform(1, new transFade(sf::Uint8(255), sf::seconds(2)));
	}

	Cinamon::~Cinamon()
	{
	}

}