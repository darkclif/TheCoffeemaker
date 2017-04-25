#include "PauseGameState.h"

namespace CMaker {
	void PauseGameState::HandleInput(const sf::Event & _event)
	{
		menuPause->HandleInput(_event);
	}

	void PauseGameState::Update(const sf::Time _time)
	{
		State::Update(_time);
	}

	void PauseGameState::Render()
	{
		getGame()->getRender().draw(fadeRect);
		State::Render();
	}

	void PauseGameState::initEntities()
	{
		menuPause = std::make_unique<CMaker::PauseMenu>(getGame());
		menuPause->addDrawQueue(this);

		sf::Vector2f lSize = getGame()->getRender().getView().getSize();
		fadeRect.setSize(sf::Vector2f(lSize.x, lSize.y) );
		fadeRect.setFillColor(sf::Color(0, 0, 0, 100));
	}

	/* Constructor / Destructor */
	PauseGameState::PauseGameState(Game* _game):
		State(_game, false, true)
	{
		initEntities();
	}

	PauseGameState::PauseGameState(Game * _game, bool _timeTrans, bool _rendTrans):
		State(_game, _timeTrans, _rendTrans)
	{
		initEntities();
	}

	PauseGameState::~PauseGameState()
	{
	}

}