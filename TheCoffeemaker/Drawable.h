#pragma once
#include <SFML/Graphics.hpp>

namespace CMaker {
	class State;

	class Drawable
	{
	public:
		void virtual		Draw(sf::RenderWindow& _render, sf::RenderStates _states = sf::RenderStates()) = 0;

		void				setLayer(sf::Uint32 _layer);
		sf::Uint32			getLayer() const;

		sf::Uint32			getGlobalDrawableId();

		/*	Enque this drawing in State drawing queue 
			
			When destructor is called this drawing should 
			delete itself from this queue.
		*/
		void				addDrawQueue(CMaker::State* _state);

							Drawable();
							~Drawable();

	private:
		/* To draw entities in correct order */
		sf::Uint32			layer;

		/* Global ID of each Drawable entity */
		const sf::Uint32	globalDrawableId;

		/* State that contains this entity in drawing queue */
		CMaker::State*		bindedDrawingState;

		/* Global ID counter */
		static sf::Uint32	GLOBAL_ID_COUNTER;
	};

}