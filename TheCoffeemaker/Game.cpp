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
		// Consts
		const sf::VideoMode VIDEO_MODE(800,600);
		const int FRAME_LIMIT = 30;
		const int ANTIALIASING = 8;
		const std::string WINDOW_NAME = "Bubus - The Coffeemaker";

		// Setup render
		sf::ContextSettings setWindow;
		setWindow.antialiasingLevel = ANTIALIASING;

		sf::RenderWindow* renWindow = new sf::RenderWindow(VIDEO_MODE, WINDOW_NAME, sf::Style::Default, setWindow);
		renWindow->setFramerateLimit(FRAME_LIMIT);
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