#include "Transform.h"

namespace CMaker {

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