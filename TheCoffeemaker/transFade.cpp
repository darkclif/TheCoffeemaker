#include "transFade.h"
#include <TheCoffeeMaker/SimpleAnimation.h>

namespace CMaker {
	/* Transform entity */
	sf::Time transFade::operator()(sf::Time _time, CMaker::SimpleAnimation* _entity)
	{
		// Transform is updated first time, get initial alpha value
		if (getTime() == sf::Time::Zero) {
			startAlpha = _entity->getColor().a;
		}
		
		Update(_time);

		// Exit if finished
		if (getTime() >= getLength()) {
			return (getTime() - getLength());
		}
		
		// Interpolate alpha
		sf::Uint8 currAlpha = startAlpha - (sf::Uint8)((startAlpha - targetAlpha) * (getTime() / getLength()));
		sf::Color currColor = _entity->getColor();

		currColor.a = currAlpha;
		_entity->setColor(currColor);

		return sf::Time::Zero;
	}

	/*
		Contructor / Destructor
	*/
	transFade::transFade(sf::Uint8 _targetAlpha, sf::Time _length):
		Transform(_length),
		targetAlpha{ _targetAlpha}
	{
		startAlpha = 0; // Not known yet
	}

	transFade::~transFade()
	{
	}

}