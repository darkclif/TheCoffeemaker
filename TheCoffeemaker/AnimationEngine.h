#pragma once
#include <map>
#include <vector>

#include <TheCoffeeMaker/Animation.h>

namespace CMaker {

	template <typename E>
	class AnimationEngine
	{
	public:
		AnimationEngine(/* SimpleAnimation& _entity */) {};
		~AnimationEngine() {};

	private:
		std::map< E, std::vector< CMaker::Animation > > mapAnimations;
	};

}