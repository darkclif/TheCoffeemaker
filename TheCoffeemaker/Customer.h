#pragma once
#include <TheCoffeeMaker/Animation.h>
#include <TheCoffeeMaker/CoffeeComposition.h>
#include <TheCoffeeMaker/CoffeeJudge.h>

namespace CMaker {

	class Customer:
		public Animation
	{
	public:
		void		Update(sf::Time _time) override;				
		void		Draw(sf::RenderWindow& _render, sf::RenderStates _states = sf::RenderStates()) override;

					Customer(sf::Vector2f _pos, int _cusId);
					~Customer();

		/* Events */
		/* Poke customer to say what he want one more time */
		void		eventPoke();
		void		eventCoffeeConsume(const Coffee& _coffee);

	private:
		/* Rects of diffrent customers */
		static const std::vector<sf::IntRect> customersRect;

		/* Coffee expectation string */
		sf::Text entSay;
		sf::Time sayCurrLength;
		bool sayShow;
		int pokes;

		static const sf::Time SAY_LENGTH;

		/* Expectation of coffee */
		const CMaker::CoffeeComposition coffeeExpectation;
		CMaker::CoffeeType coffeeType;
	};

}