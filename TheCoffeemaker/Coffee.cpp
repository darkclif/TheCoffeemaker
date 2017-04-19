#include "Coffee.h"
#include <TheCoffeeMaker/Transforms.h>

namespace CMaker {
	void Coffee::setHeat(sf::Uint8 _heat)
	{
		if (_heat <= HEAT_LIMIT && _heat >= 1) {
			heat = _heat;
		}
	}

	sf::Uint8 Coffee::getHeat()
	{
		return heat;
	}

	Coffee::Coffee(CoffeeType _type, sf::Vector2f _pos)
	{
		setTextureEnum(_type == CoffeeType::SMALL ? Texture::COFFEE_SMALL : Texture::COFFEE_BIG);
		setPosition(_pos);

		heat = 1;
		setScale(sf::Vector2f(3.f, 3.f));
		setOriginAlign(OriginAlign::MIDDLE_CENTER);
	}

	Coffee::~Coffee()
	{
	}

}