#include "transMove.h"
#include <TheCoffeeMaker/Animation.h>

namespace CMaker {
	/* Transform entity */
	sf::Time transMove::Apply(sf::Time _time, CMaker::Animation * _entity)
	{
		// Transform is updated first time, get initial position
		if (getTime() == sf::Time::Zero) {
			startPosition = _entity->getPosition();
		}

		Update(_time);

		// Exit if finished
		sf::Time timeAbove = (getTime() - getLength());
		if (timeAbove > sf::Time::Zero) {
			Reset();
			return timeAbove;
		}

		// Interpolate position
		sf::Vector2f currPosition = startPosition - (startPosition - targetPosition) * (getTime() / getLength());
		_entity->setPosition(currPosition);

		return sf::Time::Zero;
	}

	/*
		Contructor / Destructor
	*/
	transMove::transMove(sf::Vector2f _pos, sf::Time _length):
		Transform(_length),
		targetPosition{_pos}
	{
		startPosition = sf::Vector2f(0.f, 0.f); // Not known yet
	}

	transMove::~transMove()
	{

	}

}