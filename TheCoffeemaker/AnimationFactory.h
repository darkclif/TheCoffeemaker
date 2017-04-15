#pragma once
#include <TheCoffeeMaker/AnimationEngine.h>
#include <TheCoffeeMaker/Transforms.h>

namespace CMaker {

	/*
		Static class for insert commonly used animations
		to AnimationEngine. 
		
		Usage in SimpleAnimation or Animation class:
			addAnimation<PredefAnimation::FOO>(int  _animNum, CMaker::AnimationEngine* _engine)
	*/
	class AnimationFactory
	{
	public:
		enum class PredefAnimation {
			/* Fade to alpha 255 and then to 0 */
			SHOW_FADE
		};

	public:
		/* Add predefined animation to engine */
		template<PredefAnimation PA>
		static void addAnimation(int  _num, CMaker::AnimationEngine* _engine) {
			throw std::exception("Fatal: This predefined animation is not implemented!");
		}
		
		/* Specializations: */
		template<>
		static void addAnimation<PredefAnimation::SHOW_FADE>(int  _num, CMaker::AnimationEngine* _engine) {
			_engine->addAnimation(_num);
			
			_engine->addTransform(_num, new transFade(sf::Uint8(255), sf::milliseconds(2000)));
			_engine->addTransform(_num, new transWait(sf::milliseconds(1000)));
			_engine->addTransform(_num, new transFade(sf::Uint8(0), sf::milliseconds(2000)));
		}

	private:
		AnimationFactory(const AnimationFactory& ) = delete;
		AnimationFactory() = delete;
		~AnimationFactory() = delete;
	};

}