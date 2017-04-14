#pragma once
#include <map>
#include <vector>

#include <TheCoffeeMaker/Transform.h>
#include <TheCoffeeMaker/Updatable.h>

namespace CMaker {
	class SimpleAnimation;

	class AnimationEngine:
		public Updatable
	{
	public:
		void Update(sf::Time _time) override;

		AnimationEngine(CMaker::SimpleAnimation* _entity);
		~AnimationEngine();

	private:
		/* Entity to apply animations */
		CMaker::SimpleAnimation*							entity;

		std::map< int, std::vector< CMaker::Transform > >	mapAnimations;
	};

}