#include "CoffeeStack.h"

#include <TheCoffeeMaker/Tools.h>

namespace CMaker {
	/* Accesors */
	Coffee::CoffeeType CoffeeStack::getCoffeeType()
	{
		return type;
	}

	/* Constructor / Destructor */
	CoffeeStack::CoffeeStack(Coffee::CoffeeType _type, sf::Vector2f _pos):
		type{ _type}
	{
		// Set texture
		switch (_type) {
			case Coffee::CoffeeType::BIG: setTextureEnum(Texture::COFFEE_BIG_STACK); break;
			case Coffee::CoffeeType::SMALL: setTextureEnum(Texture::COFFEE_SMALL_STACK); break;
			default: throw std::exception("Coffee type not implemented!");  break;
		}

		setOriginAlign(OriginAlign::BOTTOM_CENTER);
		setScale(sf::Vector2f(3.f, 3.f));
		setPosition(_pos);
	}

	CoffeeStack::~CoffeeStack()
	{
	}

}