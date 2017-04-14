#pragma once
#include <map>
#include <vector>
#include <memory>

#include <TheCoffeeMaker/Transform.h>
#include <TheCoffeeMaker/Updatable.h>

namespace CMaker {
	class SimpleAnimation;

	class AnimationEngine:
		public Updatable
	{
	public:
		/* Update engine and transform handled entity */
		void						Update(sf::Time _time) override;

		/* Activate given animation and set first transform */
		void						runAnimation(int _animation);
		
		/* Add animation */
		void						addAnimation(int _animation);

		/* Add transform to given animation */
		void						addTransform(int _animation, CMaker::Transform* _transform);

		/* Run / stop animation */
		bool						isRunning();
		void						setRunning(bool _running);

		/* Constructor / Destructor */
									AnimationEngine(CMaker::SimpleAnimation* _entity);
									~AnimationEngine();

	private:
		/* Go to next transform or stop if transform was last on list */
		void						nextTransform();

		/* Entity to apply animation transforms */
		CMaker::SimpleAnimation*	entity;

		/* Map of different animations, each animation have its own sequence of transforms */
		std::map< /* Animation*/ int, std::vector< std::unique_ptr< CMaker::Transform > > >	
									mapAnimations;

		/* Current running animation */
		int							currAnimation;
		int							currTransform;

		/* Is engine running */
		bool						running;
	};

}