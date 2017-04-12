#pragma once
#include <memory>

#include <SFML/Graphics.hpp>

namespace CMaker {

	class StateMachine;

	class Game
	{
	public:
		void Run();

		StateMachine& getStateMachine() { return *stateMachine; };
		sf::RenderWindow& getRender() { return *renderWindow; };

		Game();
		~Game();

	private:
		sf::RenderWindow* createRender();

	private:
		std::unique_ptr< StateMachine >			stateMachine;
		std::unique_ptr< sf::RenderWindow >		renderWindow;
	};

}