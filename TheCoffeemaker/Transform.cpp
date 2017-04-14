#include "Transform.h"

namespace CMaker {
	void Transform::Update(sf::Time _time)
	{
		addTime(_time);
	}

	sf::Time Transform::getLength()
	{
		return length;
	}

	void Transform::Reset()
	{
		resetTime();
	}

	Transform::Transform(sf::Time _length):
		length{ _length}
	{
	}

	Transform::~Transform()
	{
	}

}