#pragma once
#include <TheCoffeeMaker/Transform.h>

namespace CMaker {

	class transMove:
		public Transform
	{
	public:
		sf::Time			Apply(sf::Time _time, CMaker::SimpleAnimation* _entity) override;
							
							transMove(sf::Vector2f _pos, sf::Time _length);
							~transMove();

	private:
		sf::Vector2f		targetPosition;
		sf::Vector2f		startPosition;
	};

}