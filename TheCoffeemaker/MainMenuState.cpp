#include "MainMenuState.h"
#include <TheCoffeeMaker/Game.h>
#include <TheCoffeeMaker/StateMachine.h>

namespace CMaker {
	/*
		State managment
	*/
	void MainMenuState::HandleInput(const sf::Event & _event)
	{
		menuMain->HandleInput(_event);
	}

	void MainMenuState::initEntities()
	{
		// ENTITIES
		animLogo = std::make_unique<CMaker::SimpleAnimation>(CMaker::Texture::SMALL_LOGO, sf::Vector2f(570, 380));
		animLogo->setOriginAlign(OriginAlign::MIDDLE_CENTER);
		animLogo->loadAnimation<AnimationFactory::PredefAnimation::WOBBLE>();

		animBubus = std::make_unique<CMaker::SimpleAnimation>(CMaker::Texture::BUBUS_FACE, sf::Vector2f(570, 180));
		animBubus->setOriginAlign(OriginAlign::MIDDLE_CENTER);
		animBubus->loadAnimation<AnimationFactory::PredefAnimation::LEVITATE>();

		// MAIN MENU
		menuMain = std::make_unique<CMaker::MainMenu>(getGame());
		menuMain->setPosition(100.f, 100.f);

		// Add to queues
		animBubus->addUpdateQueue(this);
		animLogo->addUpdateQueue(this);

		animBubus->addDrawQueue(this);
		animLogo->addDrawQueue(this);
		menuMain->addDrawQueue(this);
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