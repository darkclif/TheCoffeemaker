#pragma once
#include <TheCoffeeMaker/Transform.h>

namespace CMaker {

	class transScale:
		public Transform
	{
	public:
		sf::Time			Apply(sf::Time _time, CMaker::Animation* _entity) override;

							transScale(sf::Vector2f _targetScale, sf::Time _length);
							~transScale();

	private:
		sf::Vector2f		targetScale;
		sf::Vector2f		startScale;
	};

}