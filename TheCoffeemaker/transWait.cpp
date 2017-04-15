#include "transWait.h"

namespace CMaker {
	sf::Time transWait::Apply(sf::Time _time, CMaker::SimpleAnimation * _entity)
	{
		Update(_time);

		// Exit if finished
		sf::Time timeAbove = (getTime() - getLength());
		if (timeAbove > sf::Time::Zero) {
			Reset();
			return timeAbove;
		}

		return sf::Time::Zero;
	}

	transWait::transWait(sf::Time _length):
		Transform(_length)
	{
	}

	transWait::~transWait()
	{
	}

}