#pragma once
#include <TheCoffeeMaker/Updatable.h>

namespace CMaker {
	class Animation;

	class Transform:
		protected Updatable
	{
	public:
		/* Transform entity 
			@return Time left, that transform did not consume.
		*/
		sf::Time virtual		Apply(sf::Time _time, CMaker::Animation* _entity) = 0;

		void					Reset();

								Transform(sf::Time _length = sf::Time::Zero);
		virtual					~Transform();

	protected:
		sf::Time				getLength();

	private:
		const sf::Time			length;
	};

}