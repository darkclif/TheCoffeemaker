#pragma once
#include <TheCoffeeMaker/AnimateEntity.h>
#include <TheCoffeeMaker/AnimationEngine.h>

namespace CMaker {

	class SimpleAnimation:
		public AnimateEntity
	{
	public:
		void						Update(sf::Time _time) override;

									SimpleAnimation(CMaker::Texture _enumTexture, sf::Vector2f _pos);
									SimpleAnimation();
		virtual						~SimpleAnimation();

	protected:
		CMaker::AnimationEngine		animationEngine;
	};

}