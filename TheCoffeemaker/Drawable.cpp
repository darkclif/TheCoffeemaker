#include "Drawable.h"
#include <TheCoffeeMaker/Console.h>
#include <TheCoffeeMaker/State.h>

namespace CMaker {
	/* Gloal drawable id counter */
	sf::Uint32 Drawable::GLOBAL_ID_COUNTER = 0;

	/* Layers accesors */
	void Drawable::setLayer(sf::Uint32 _layer)
	{
		layer = _layer;
	}

	sf::Uint32 Drawable::getLayer() const
	{
		return layer;
	}

	/* Global drawable id */
	sf::Uint32 Drawable::getGlobalDrawableId()
	{
		return globalDrawableId;
	}

	void Drawable::addDrawQueue(CMaker::State * _state)
	{
		if (bindedDrawingState != nullptr) {
			C_DEBUG << S_WARNING << "This entity is already in a state queue, operation skipped." << std::endl;
			return;
		}

		_state->enqueDrawable(this);
		bindedDrawingState = _state;
	}

	/*
		Constructor / Destructor
	*/
	Drawable::Drawable():
		layer{ 0 },
		globalDrawableId{ Drawable::GLOBAL_ID_COUNTER++ },
		bindedDrawingState( nullptr )
	{
	}

	Drawable::~Drawable()
	{
		// Deque this entity from binded state
		if (bindedDrawingState != nullptr) {
			bindedDrawingState->dequeDrawable(getGlobalDrawableId());
		}
	}

}