#pragma once
#include <SFML/System.hpp>

namespace CMaker {
	class State;

	class Updatable
	{
	public:
		void virtual		Update(sf::Time _time);

		sf::Uint32			getGlobalUpdatableId();

		/*	Enque this drawing in State drawing queue

		When destructor is called this drawing should
		delete itself from this queue.
		*/
		void				addUpdateQueue(CMaker::State* _state);

							Updatable();
		virtual 			~Updatable();

	protected:
		void				addTime(sf::Time _time);
		void				resetTime();
		sf::Time			getTime();

	private:
		/* Time passed */
		sf::Time			time;

		/* Global ID of each Updatable entity */
		const sf::Uint32	globalUpdatableId;

		/* State that contains this entity in update queue */
		CMaker::State*		bindedUpdatingState;

		/* Global ID counter */
		static sf::Uint32	GLOBAL_ID_COUNTER;
	};

}