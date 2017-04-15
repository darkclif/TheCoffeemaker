#pragma once
#include <TheCoffeeMaker/Animation.h>
#include <TheCoffeeMaker/AnimationFactory.h>

namespace CMaker {

	/*
		Class for creating simple game units with one 
		animation (in most cases). For example logos,
		small entities without any mechanics.
	*/
	class SimpleAnimation:
		public Animation
	{
	public:
		template <CMaker::AnimationFactory::PredefAnimation PA>
		void loadAnimation(){
			CMaker::AnimationFactory::addAnimation<PA>(1, &animationEngine);
		}

	public:
			
			SimpleAnimation(CMaker::Texture _enumTexture, sf::Vector2f _pos);
			SimpleAnimation(CMaker::Texture _enumTexture);
			SimpleAnimation();
			~SimpleAnimation();
	};

}