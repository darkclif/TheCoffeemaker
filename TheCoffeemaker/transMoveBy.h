#pragma once
#include <TheCoffeeMaker/Transform.h>

namespace CMaker {

	class transMoveBy:
		public Transform
	{
	public:
		sf::Time			Apply(sf::Time _time, CMaker::Animation* _entity) override;

							transMoveBy(sf::Vector2f _pos, sf::Time _length);
							~transMoveBy();

	private:
		sf::Vector2f		deltaPosition;
		sf::Vector2f		startPosition;
	};

}