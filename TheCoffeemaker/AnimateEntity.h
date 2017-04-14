#pragma once
#include <TheCoffeeMaker/Updatable.h>
#include <TheCoffeeMaker/Unit.h>

namespace CMaker {

	class AnimateEntity:
		public Updatable,
		public Unit
	{
	public:
		AnimateEntity();
		virtual ~AnimateEntity();
	};

}