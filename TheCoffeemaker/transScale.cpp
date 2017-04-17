#include "transScale.h"
#include <TheCoffeeMaker/Animation.h>

namespace CMaker {
	sf::Time transScale::Apply(sf::Time _time, CMaker::Animation * _entity)
	{
		// Transform is updated first time, get initial alpha value
		if (getTime() == sf::Time::Zero) {
			startScale = _entity->getScale();
		}

		Update(_time);

		// Exit if finished
		sf::Time timeAbove = (getTime() - getLength());
		if (timeAbove > sf::Time::Zero) {
			Reset();
			return timeAbove;
		}

		// Interpolate alpha
		sf::Vector2f currScale = startScale - (startScale - targetScale) * (getTime() / getLength());
		_entity->setScale(currScale);

		return sf::Time::Zero;
	}

	transScale::transScale(sf::Vector2f _targetScale, sf::Time _length):
		Transform(_length),
		targetScale{ _targetScale }
	{
		startScale = sf::Vector2f(); // Not known yet
	}

	transScale::~transScale()
	{
	}

}