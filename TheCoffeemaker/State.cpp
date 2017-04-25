#include "State.h"
#include "Game.h"

#include <TheCoffeeMaker/Console.h>

namespace CMaker {
	void State::Update(const sf::Time _time)
	{
		for (auto lUpdatablePtr : queueUpdatable) {
			lUpdatablePtr->Update(_time);
		}
	}

	void State::Render()
	{
		sf::RenderWindow& render = getGame()->getRender();

		for (auto lDrawablePtr : queueDrawable) {
			lDrawablePtr->Draw(render);
		}
	}

	/* Drawing queue managment */
	void State::enqueDrawable(Drawable* _entity)
	{
		queueDrawable.insert(_entity);
	}

	void State::dequeDrawable(sf::Uint32 _globalId)
	{
		/*	
			First search across whole queue to check if there
			is no duplicated entities inserted. If not, then
			delete that one and return or make loop again to
			delete remaining entities.
		*/
		auto findIt = queueDrawable.end();
		int lCount = 0; // There should not be duplicated entities in queue, but check it
		bool lFirstSearch = true;

		do {
			for (auto it = queueDrawable.begin(); it != queueDrawable.end(); ++it) {
				if ((*it)->getGlobalDrawableId() == _globalId) {
					findIt = it;

					if (lFirstSearch) lCount++;
					if (!lFirstSearch) it = queueDrawable.end();
				}
			}

			if (findIt != queueDrawable.end()) {
				queueDrawable.erase(findIt);
				lCount--;
			}
		} while (lCount > 0);
		
	}

	/* Updating queue managment */
	void State::enqueUpdatable(Updatable* _entity)
	{
		queueUpdatable.push_back(_entity);
	}

	void State::dequeUpdatable(sf::Uint32 _globalId)
	{
		/*
			First search across whole queue to check if there
			is no duplicated entities inserted. If not, then
			delete that one and return or make loop again to
			delete remaining entities.
		*/
		auto findIt = queueUpdatable.end();
		int lCount = 0; // There should not be duplicated entities in queue, but check it
		bool lFirstSearch = true;

		do {
			for (auto it = queueUpdatable.begin(); it != queueUpdatable.end(); ++it) {
				if ((*it)->getGlobalUpdatableId() == _globalId) {
					findIt = it;

					if (lFirstSearch) lCount++;
					if (!lFirstSearch) it = queueUpdatable.end();
				}
			}

			if (findIt != queueUpdatable.end()) {
				queueUpdatable.erase(findIt);
				lCount--;
			}
		} while (lCount > 0);

	}

	/* Transparency accesors */
	bool State::isTimeTrans()
	{
		return timeTrans;
	}

	bool State::isRendTrans()
	{
		return rendTrans;
	}

	/* Binded game main instance */
	Game * State::getGame()
	{
		return game;
	}

	/* Constructor / Destructor */
	State::State(Game* _game) : game{ _game }
	{
		timeTrans = false;
		rendTrans = false;
	}

	State::State(Game* _game, bool _timeTrans, bool _rendTrans) :
		game{ _game },
		timeTrans{ _timeTrans },
		rendTrans{ _rendTrans }
	{
	}

	State::~State()
	{
	}
}