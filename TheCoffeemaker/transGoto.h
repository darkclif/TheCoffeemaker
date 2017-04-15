#pragma once
#include <TheCoffeeMaker/Transform.h>

namespace CMaker {
	class AnimationEngine;

	class transGoto :
		public Transform
	{
	public:
		sf::Time					Apply(sf::Time _time, CMaker::SimpleAnimation* _entity) override;

									transGoto(int _label, CMaker::AnimationEngine* _engine);
									~transGoto();

	private:
		int							targetTransLabel;
		CMaker::AnimationEngine*	engine;
	};

}