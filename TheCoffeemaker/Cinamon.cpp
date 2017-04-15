#include "Cinamon.h"
#include <TheCoffeeMaker/Transforms.h>
#include <TheCoffeeMaker/ResourceManager.h>

namespace CMaker {

	Cinamon::Cinamon(sf::Vector2f _pos):
		SimpleAnimation(CMaker::Texture::NONE, _pos)
	{
		setOriginAlign();

		animationEngine.addAnimation(1);
		animationEngine.addTransform(1, new transRotate(-50.f, sf::seconds(1)));
		animationEngine.addTransform(1, new transRotate(100.f, sf::seconds(1)));
		animationEngine.addTransform(1, new transRotate(-50.f, sf::seconds(1)));
	}

	Cinamon::~Cinamon()
	{
	}

}