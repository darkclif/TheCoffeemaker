#pragma once
#include <TheCoffeeMaker/Transform.h>
#include <SFML/System.hpp>

namespace CMaker {

	class transFade :
		public Transform
	{
	public:
		sf::Time			operator()(sf::Time _time, CMaker::SimpleAnimation* _entity) override;

							transFade(sf::Uint8 _targetAlpha, sf::Time _length);
							~transFade();

	private:
		sf::Uint8			targetAlpha;
		sf::Uint8			startAlpha;
	};

}