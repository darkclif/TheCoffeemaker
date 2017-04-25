#pragma once
#include <TheCoffeeMaker/Animation.h>
#include <TheCoffeeMaker/HeatBar.h>

namespace CMaker {
	class CoffeeMachine;

	class Coffee:
		public Animation
	{
	public:
		enum class CoffeeType {
			SMALL,
			BIG
		};

		/* Get coffee type */
		CoffeeType		getCoffeeType();

		/* Detach, attach coffee cup from machine */
		void			detachFromMachine();
		void			attachToMachine(CoffeeMachine* _machine);

		/* Manage heat */
		void			setHeat(sf::Uint8 _heat);
		void			addHeat(sf::Uint8 _heat);
		sf::Uint8		getHeat();

		/* Constructor / Destructor */
						Coffee(CoffeeType _type, sf::Vector2f _pos);
						~Coffee();

	private:
		/* Heat indicator */
		HeatBar*					entHeatBar;

		/* Coffee machine attachedd */
		CoffeeMachine*				attachedMachine;

		/* Get coffee type */
		CoffeeType					coffeeType;

		/* Heat managment */
		static const sf::Uint8	HEAT_LIMIT = 9;
		sf::Uint8				heat;
	};

}