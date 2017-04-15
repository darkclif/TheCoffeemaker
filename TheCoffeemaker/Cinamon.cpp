#include "Cinamon.h"
#include <TheCoffeeMaker/Transforms.h>
#include <TheCoffeeMaker/ResourceManager.h>

namespace CMaker {

	Cinamon::Cinamon(sf::Vector2f _pos):
		Animation(CMaker::Texture::SMALL_LOGO, _pos)
	{
		setOriginAlign();
		setColorAlpha(0);

		animationEngine.addAnimation(1);
		
		animationEngine.addTransform(1, new transMove(sf::Vector2f(300.f, 300.f), sf::seconds(2)));
		animationEngine.addLabel(1, 1);
		animationEngine.addTransform(1, new transFade(255, sf::seconds(3)));
		animationEngine.addTransform(1, new transWait(sf::seconds(3)));
		animationEngine.addTransform(1, new transRotate(-50.f, sf::seconds(3)));
		animationEngine.addTransform(1, new transRotate(100.f, sf::seconds(3)));
		animationEngine.addTransform(1, new transRotate(-50.f,sf::seconds(3)));
		animationEngine.addTransform(1, new transFade(0, sf::seconds(3)));
		animationEngine.addGoto(1, 1);

		animationEngine.runAnimation(1);
	}

	Cinamon::~Cinamon()
	{
	}

}