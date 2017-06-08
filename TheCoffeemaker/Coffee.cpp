#include "Coffee.h"
#include <TheCoffeeMaker/Transforms.h>
#include <TheCoffeeMaker/CoffeeMachine.h>

namespace CMaker {
	Coffee::CoffeeType Coffee::getCoffeeType()
	{
		return coffeeType;
	}
	
	void Coffee::detachFromMachine()
	{
		if (attachedMachine) {
			attachedMachine->detachCoffee();
			attachedMachine = nullptr;
		}
	}

	void Coffee::attachToMachine(CoffeeMachine * _machine)
	{
		// Detach if there is already attached machine
		if (attachedMachine) {
			attachedMachine->detachCoffee();
		}

		// Attach to new machine
		attachedMachine = _machine;
		attachedMachine->attachCoffee(this);
	}

	/* Manage heat of coffee */
	void Coffee::setHeat(sf::Uint8 _heat)
	{
		if (_heat <= HEAT_LIMIT && _heat >= 1) {
			heat = _heat;
		}
	}

	void Coffee::addHeat(sf::Uint8 _heat)
	{
		heat += _heat;
		if (heat > HEAT_LIMIT) {
			heat = HEAT_LIMIT;
		}
	}

	sf::Uint8 Coffee::getHeat()
	{
		return heat;
	}

	/* Constructor / Destructor */
	Coffee::Coffee(CoffeeType _type, sf::Vector2f _pos):
		heat{1},
		coffeeType{_type}
	{
		// Setup coffee
		setTextureEnum(_type == CoffeeType::SMALL ? Texture::COFFEE_SMALL : Texture::COFFEE_BIG);
		setPosition(_pos);
		setScale(sf::Vector2f(3.f, 3.f));
		setOriginAlign(OriginAlign::MIDDLE_CENTER);

	}

	Coffee::~Coffee()
	{
	}

}