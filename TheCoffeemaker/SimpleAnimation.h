#pragma once
#include <TheCoffeeMaker/AnimateEntity.h>
#include <TheCoffeeMaker/AnimationEngine.h>

namespace CMaker {

	class SimpleAnimation:
		public AnimateEntity
	{
	public:
								SimpleAnimation();
								~SimpleAnimation();

	protected:
		// TODO:

	private:
		CMaker::AnimationEngine	animEngine;
	};

}