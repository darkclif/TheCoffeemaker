#include "Game.h"
#include <TheCoffeeMaker/StateMachine.h>

namespace CMaker {

	void Game::Run()
	{
		stateMachine->reqPushState(EnumState::INTRO);
		stateMachine->Run();
	}

	sf::RenderWindow* Game::createRender()
	{
		sf::ContextSettings setWindow;
		setWindow.antialiasingLevel = 8;

		sf::RenderWindow* renWindow = new sf::RenderWindow(sf::VideoMode(1300, 1000), "SFML works!", sf::Style::Default, setWindow);
		renWindow->setFramerateLimit(30);
		renWindow->resetGLStates();

		return renWindow;
	}

	Game::Game()
	{
		std::unique_ptr<StateMachine> tmpMachine(new StateMachine(this));
		this->stateMachine = std::move(tmpMachine);

		std::unique_ptr<sf::RenderWindow> tmpWindow(this->createRender());
		this->renderWindow = std::move(tmpWindow);	
	}

	Game::~Game()
	{
	}
}