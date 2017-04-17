#include "Updatable.h"
#include <TheCoffeeMaker/State.h>
#include <TheCoffeeMaker/Console.h>

namespace CMaker {
	/* Gloal drawable id counter */
	sf::Uint32 Updatable::GLOBAL_ID_COUNTER = 0;

	/* Update time */
	void Updatable::Update(sf::Time _time)
	{
		addTime(_time);
	}

	sf::Uint32 Updatable::getGlobalUpdatableId()
	{
		return globalUpdatableId;
	}

	void Updatable::addUpdateQueue(CMaker::State * _state)
	{
		if (bindedUpdatingState != nullptr) {
			C_DEBUG << S_WARNING << "This entity is already in a state queue, operation skipped." << std::endl;
			return;
		}

		_state->enqueUpdatable(this);
		bindedUpdatingState = _state;
	}

	/*
		Manage time
	*/
	void Updatable::addTime(sf::Time _time)
	{
		time += _time;
	}

	void Updatable::resetTime()
	{
		time = sf::Time();
	}

	sf::Time Updatable::getTime()
	{
		return time;
	}

	/*
		Constructor / Destructor
	*/
	Updatable::Updatable():
		globalUpdatableId{ Updatable::GLOBAL_ID_COUNTER++ },
		bindedUpdatingState( nullptr )
	{

	}

	Updatable::~Updatable()
	{
		// Deque this entity from binded state
		if (bindedUpdatingState != nullptr) {
			bindedUpdatingState->dequeDrawable(getGlobalUpdatableId());
		}
	}

}