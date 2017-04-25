#pragma once
#include <TheCoffeeMaker/UpdatableUnit.h>
#include <TheCoffeeMaker/Coffee.h>

namespace CMaker {

	class CoffeeMachine:
		public UpdatableUnit
	{
	public:
		/* Update */
		void		Update(sf::Time _time) override;

		/* Attach coffee */
		void		attachCoffee(Coffee* _coffee);
		void		detachCoffee();

		/* Constructor / Destructor */
					CoffeeMachine(sf::Vector2f _pos);
					~CoffeeMachine();

	private:
		/* Max and min done texture */
		static const sf::Uint8 MAX_DONE_BARS = 5;
		static const sf::Uint8 MIN_DONE_BARS = 0;

		/* Done bars setter */
		void		updateDoneBars();

	private:
		/* Time needed to fill one bar of heat */
		static const sf::Time TIME_PER_HEAT;

		/* Position to align coffee cup */
		static const sf::Vector2f COFFEE_SMALL_POSTION;
		static const sf::Vector2f COFFEE_BIG_POSTION;

		/* Attached coffee */
		Coffee*		attachedCoffee;
		
		/* Set texture rect */
		void		setMachineTextureRect();

		/* Done indicator */
		sf::Uint8	doneBars;
	};

}