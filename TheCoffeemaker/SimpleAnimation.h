#pragma once
#include <TheCoffeeMaker/Updatable.h>
#include <TheCoffeeMaker/Unit.h>

namespace CMaker {

	class SimpleAnimation:
		public Updatable,
		public Unit
	{
	public:

		SimpleAnimation();
		~SimpleAnimation();
	};

}