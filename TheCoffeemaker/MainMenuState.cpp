#include "MainMenuState.h"
#include <TheCoffeeMaker/Game.h>

namespace CMaker {
	/*
		State managment
	*/
	void MainMenuState::HandleInput(const sf::Event & _event)
	{
		menuMain->HandleInput(_event);
	}

	void MainMenuState::Update(const sf::Time _time)
	{

	}

	void MainMenuState::Render()
	{
		// Draw entities
		sf::RenderWindow& render = getGame()->getRender();

		menuMain->Draw(render);
	}

	void MainMenuState::initEntities()
	{
		// Menu
		menuMain = std::make_unique<CMaker::Menu>();
		menuMain->addPage(1);
		menuMain->addEntry(1, "Start");
		menuMain->addEntry(1, "Options");
		menuMain->addEntry(1, "Credits");
		menuMain->addEntry(1, "Exit");
	}

	/*
		Constructor / Destructor
	*/
	MainMenuState::MainMenuState(Game* _game, bool _timeTrans, bool _rendTrans):
		State(_game, _timeTrans, _rendTrans)
	{
		initEntities();
	}

	MainMenuState::MainMenuState(Game* _game):
		State(_game)
	{
		initEntities();
	}

	MainMenuState::~MainMenuState()
	{

	}

}