#include "Cinamon.h"
#include <TheCoffeeMaker/Transforms.h>
#include <TheCoffeeMaker/ResourceManager.h>

namespace CMaker {

	Cinamon::Cinamon(sf::Vector2f _pos):
		Animation(CMaker::Texture::SMALL_LOGO, _pos)
	{
		setOriginAlign();

		animationEngine.addAnimation(1);
		
		animationEngine.addTransform(1, new transMove(sf::Vector2f(300.f, 300.f), sf::seconds(2)));
		animationEngine.addTransform(1, new transRotate(-30.f, sf::milliseconds(1000)));
		animationEngine.addLabel(1, 1);
		animationEngine.addTransform(1, new transRotate(10.f, sf::seconds(1)));
		animationEngine.addTransform(1, new transRotate(-10.f,sf::seconds(1)));
		animationEngine.addGoto(1, 1);

		animationEngine.runAnimation(1);
	}

	Cinamon::~Cinamon()
	{
	}

}