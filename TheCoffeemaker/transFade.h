#pragma once
#include <TheCoffeeMaker/Transform.h>

namespace CMaker {

	class transFade :
		public Transform
	{
	public:
		sf::Time			Apply(sf::Time _time, CMaker::Animation* _entity) override;

							transFade(sf::Uint8 _targetAlpha, sf::Time _length);
							~transFade();

	private:
		sf::Uint8			targetAlpha;
		sf::Uint8			startAlpha;
	};

}