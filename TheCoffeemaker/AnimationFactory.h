#pragma once
#include <TheCoffeeMaker/AnimationEngine.h>
#include <TheCoffeeMaker/Transforms.h>

namespace CMaker {

	/*
		Static class for inserting commonly used animations
		to AnimationEngine. 
		
		Usage in SimpleAnimation or Animation class:
			addAnimation<PredefAnimation::FOO>(int  _animNum, CMaker::AnimationEngine* _engine)
	*/
	class AnimationFactory
	{
	public:
		enum class PredefAnimation {
			/* Instant alpha to 0 then slow fade to 255 */
			SLOW_SHOW, 
			
			/* Fade to alpha 255 and then to 0 */
			SHOW_FADE,

			/* Scale from 0.f to 1.f and shake */
			SCALE_SHOW,

			/* Wobble right and left */
			WOBBLE,

			/* Levitate up and a little down */
			LEVITATE
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
		
		template<>
		static void addAnimation<PredefAnimation::SCALE_SHOW>(int  _num, CMaker::AnimationEngine* _engine) {
			_engine->addAnimation(_num);

			_engine->addTransform(_num, new transScale(sf::Vector2f(1.f, 1.f), sf::milliseconds(500)));
		}

		template<>
		static void addAnimation<PredefAnimation::WOBBLE>(int  _num, CMaker::AnimationEngine* _engine) {
			_engine->addAnimation(_num);

			_engine->addTransform(_num, new transRotate(-5.f, sf::milliseconds(5000)));
			_engine->addLabel(_num, 1);
			_engine->addTransform(_num, new transRotate(10.f, sf::milliseconds(7000)));
			_engine->addTransform(_num, new transWait(sf::milliseconds(500)));
			_engine->addTransform(_num, new transRotate(-10.f, sf::milliseconds(7000)));
			_engine->addTransform(_num, new transWait(sf::milliseconds(500)));
			_engine->addGoto(_num, 1);
		}

		template<>
		static void addAnimation<PredefAnimation::LEVITATE>(int  _num, CMaker::AnimationEngine* _engine) {
			_engine->addAnimation(_num);

			_engine->addLabel(_num, 1);
			_engine->addTransform(_num, new transMoveBy(sf::Vector2f(0.f, -10.f), sf::milliseconds(7000)));
			_engine->addTransform(_num, new transWait(sf::milliseconds(1000)));
			_engine->addTransform(_num, new transMoveBy(sf::Vector2f(0.f, 10.f), sf::milliseconds(7000)));
			_engine->addTransform(_num, new transWait(sf::milliseconds(1000)));
			_engine->addGoto(_num, 1);
		}

		template<>
		static void addAnimation<PredefAnimation::SLOW_SHOW>(int  _num, CMaker::AnimationEngine* _engine) {
			_engine->addAnimation(_num);
			
			_engine->addLabel(_num, 1);
			_engine->addTransform(_num, new transFade(sf::Uint8(255), sf::milliseconds(2000)));
			_engine->addGoto(_num, 1);
		}

	private:
		AnimationFactory(const AnimationFactory& ) = delete;
		AnimationFactory() = delete;
		~AnimationFactory() = delete;
	};

}