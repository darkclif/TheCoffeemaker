#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <memory>

namespace CMaker {
	class Game;

	class State
	{
	public:
		typedef std::unique_ptr<State> Ptr;

		void virtual HandleInput(const sf::Event& _event) = 0;
		void virtual Update(const sf::Time _time) = 0;
		void virtual Render() = 0;

		bool isTimeTrans();
		bool isRendTrans();

		State(Game* _game);
		State(Game* _game, bool _timeTrans, bool _rendTrans);
		virtual ~State();

	protected:
		Game* getGame();

	private:
		Game* game;

		bool timeTrans; /* Pass time to states below */
		bool rendTrans; /* Render states below */
	};

}