#pragma once
#include <TheCoffeeMaker/Animation.h>
#include <TheCoffeeMaker/CoffeeCompositionView.h>

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

		typedef std::unique_ptr<CMaker::Coffee> UniqPtr;
		typedef std::shared_ptr<CMaker::Coffee> SharPtr;

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
		//HeatBar*					entHeatBar;

		/* Coffee machine attachedd */
		CoffeeMachine*				attachedMachine;

		/* Get coffee type */
		CoffeeType					coffeeType;

		/* Heat managment */
		static const sf::Uint8	HEAT_LIMIT = 9;
		sf::Uint8				heat;
	};

}