#pragma once
#include <TheCoffeeMaker/State.h>
#include <TheCoffeeMaker/PauseMenu.h>

namespace CMaker {

	class PauseGameState:
		public State
	{
	public:
		void					HandleInput(const sf::Event& _event) override;
		void					Update(const sf::Time _time) override;
		void					Render() override;

		void					initEntities();

		/* Constructor / Destructor */
								PauseGameState(Game* _game);
								PauseGameState(Game* _game, bool _timeTrans, bool _rendTrans);
								~PauseGameState();

	private:
		std::unique_ptr<CMaker::PauseMenu>	menuPause;
		sf::RectangleShape					fadeRect;
	};

}