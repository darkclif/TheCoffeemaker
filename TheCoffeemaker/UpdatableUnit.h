#pragma once
#include <TheCoffeeMaker/Updatable.h>
#include <TheCoffeeMaker/Unit.h>

namespace CMaker {

	class UpdatableUnit:
		public Updatable,
		public Unit
	{
	public:
							UpdatableUnit(CMaker::Texture _enumTexture, sf::Vector2f _pos);
							UpdatableUnit();
		virtual				~UpdatableUnit();
	};

}