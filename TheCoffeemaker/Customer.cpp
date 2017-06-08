#include "Customer.h"

#include <TheCoffeeMaker/AnimationFactory.h>

namespace CMaker {
	void Customer::Update(sf::Time _time)
	{
		Animation::Update(_time);

		/* Customer logic */

	}

	const std::vector<sf::IntRect> Customer::customersRect = {
		sf::IntRect(0,0,42,42),
		sf::IntRect(43,0,42,42),
		sf::IntRect(85,0,42,42),
	};

	Customer::Customer(sf::Vector2f _pos, int _cusId):
		Animation(CMaker::Texture::CUSTOMERS, _pos)
	{
		this->setColorAlpha(0);
		this->setTextureRect(Customer::customersRect.at(_cusId));
		this->setScale(sf::Vector2f(4.f, 4.f));
	
		AnimationFactory::addAnimation<AnimationFactory::PredefAnimation::SLOW_SHOW>(1, &(this->animationEngine));
		this->animationEngine.runAnimation(1);
	}

	Customer::~Customer()
	{

	}

}