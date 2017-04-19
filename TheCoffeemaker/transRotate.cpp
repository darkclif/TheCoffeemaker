#include "transRotate.h"
#include <TheCoffeeMaker/Animation.h>

namespace CMaker {
	/* Transform entity */
	sf::Time transRotate::Apply(sf::Time _time, CMaker::Animation * _entity)
	{
		// Transform is updated first time, get initial position
		if (getTime() == sf::Time::Zero) {
			startRotation = _entity->getRotation();
		}

		Update(_time);

		// Exit if finished
		sf::Time timeAbove = (getTime() - getLength());
		float interpolation;
		if (timeAbove > sf::Time::Zero) {
			interpolation = 1.f;
			Reset();
		}
		else {
			timeAbove = sf::Time::Zero;
			interpolation = (getTime() / getLength());
		}

		// Interpolate position
		float currRotation = startRotation + ( targetRotation * interpolation );
		_entity->setRotation(currRotation);

		return timeAbove;
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