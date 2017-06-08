#pragma once
#include <TheCoffeeMaker/State.h>

#include <TheCoffeeMaker/Unit.h>
#include <TheCoffeeMaker/SimpleAnimation.h>

#include <TheCoffeeMaker/Coffee.h>
#include <TheCoffeeMaker/Bin.h>
#include <TheCoffeeMaker/CoffeeStack.h>
#include <TheCoffeeMaker/CoffeeMachine.h>

#include <TheCoffeeMaker/Customer.h>

#include <TheCoffeeMaker/Game.h>

#include <memory>

namespace CMaker {

	class GameLevelState:
		public State
	{
	public:
		void					HandleInput(const sf::Event& _event) override;
		void					Update(const sf::Time _time) override;
		void					Render() override;

		void					initEntities();

								GameLevelState(Game* _game);
								GameLevelState(Game* _game, bool _timeTrans, bool _rendTrans);
								~GameLevelState();

	private:
		/* Units */
		int points;

		sf::Text txtPoints;

		std::vector< std::unique_ptr<CMaker::Customer> >	entCustomers;

		std::unique_ptr<CMaker::Unit>	entTable;
		std::unique_ptr<CMaker::Unit>	entBackground;
		std::unique_ptr<CMaker::Bin>	entBin;
		std::unique_ptr<CMaker::CoffeeMachine> entCoffeeMachine;

		std::vector<std::unique_ptr<CMaker::CoffeeStack>>	entCoffeeStacks;
		std::vector<std::unique_ptr<CMaker::Coffee>>		entCoffeeList;

		CMaker::Unit*					draggedObject;

		/* Events */
		void							onMouseLeftPressed(sf::Event _event);
		void							onMouseLeftReleased(sf::Event _event);
		void							onMouseMoved(sf::Event _event);

		void							spawnCoffee(Coffee::CoffeeCupSize _type, sf::Vector2f _pos);
		bool							dragObject(sf::Vector2f _pos);
	};

}