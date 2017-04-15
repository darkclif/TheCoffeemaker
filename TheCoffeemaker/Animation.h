#pragma once
#include <TheCoffeeMaker/UpdatableUnit.h>
#include <TheCoffeeMaker/AnimationEngine.h>

namespace CMaker {

	class Animation:
		public UpdatableUnit
	{
	public:
		void						Update(sf::Time _time) override;

									Animation(CMaker::Texture _enumTexture, sf::Vector2f _pos);
									Animation();
		virtual						~Animation();

	protected:
		CMaker::AnimationEngine		animationEngine;

	};

}