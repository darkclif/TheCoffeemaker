#include "transRotate.h"
#include <TheCoffeeMaker/SimpleAnimation.h>

namespace CMaker {
	/* Transform entity */
	sf::Time transRotate::Apply(sf::Time _time, CMaker::SimpleAnimation * _entity)
	{
		// Transform is updated first time, get initial position
		if (getTime() == sf::Time::Zero) {
			startRotation = _entity->getRotation();
		}

		Update(_time);

		// Exit if finished
		sf::Time timeAbove = (getTime() - getLength());
		if (timeAbove > sf::Time::Zero) {
			Reset();
			return timeAbove;
		}

		// Interpolate position
		float currRotation = startRotation + ( targetRotation * (getTime() / getLength()) );
		_entity->setRotation(currRotation);

		return sf::Time::Zero;
	}

	/*
		Contructor / Destructor
	*/
	transRotate::transRotate(float _rotation, sf::Time _length):
		Transform(_length),
		targetRotation{ _rotation }
	{
		startRotation = 0.f; // Not known yet
	}

	transRotate::~transRotate()
	{
	}

}