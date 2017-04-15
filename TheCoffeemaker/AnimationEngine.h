#pragma once
#include <map>
#include <vector>
#include <memory>

#include <TheCoffeeMaker/Transform.h>
#include <TheCoffeeMaker/Updatable.h>

namespace CMaker {
	class Animation;
	class transGoto;

	class AnimationEngine:
		public Updatable
	{
	public:
		friend class				transGoto;

		/* Update engine and transform handled entity */
		void						Update(sf::Time _time) override;

		/* Activate given animation and set first transform */
		void						runAnimation(int _animation);
		
		/* Add animation */
		void						addAnimation(int _animation);

		/* Add transform to given animation */
		void						addTransform(int _animation, CMaker::Transform* _transform);
		void						addGoto(int _animation, int _label);
		void						addLabel(int _animation, int _label);

		/* Run / stop animation */
		bool						isRunning();
		void						setRunning(bool _running);

		/* Constructor / Destructor */
									AnimationEngine(CMaker::Animation* _entity);
									~AnimationEngine();

	private:
		/* Go to next transform or stop if transform was last on list */
		void						nextTransform();

		/* Go to transform with label */
		void						goToTransform(int _label);

		/* Entity to apply animation transforms */
		CMaker::Animation*	entity;

		/* Map of different animations, each animation have its own sequence of transforms */
		std::map< /* Animation*/ int, std::vector< std::unique_ptr< CMaker::Transform > > >	
									mapAnimations;

		/* Current running animation */
		sf::Uint32					currAnimation;
		sf::Uint32					currTransform;

		/* Is engine running */
		bool						running;
	};

}