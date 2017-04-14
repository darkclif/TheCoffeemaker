#pragma once
#include <TheCoffeeMaker/Updatable.h>

namespace CMaker {
	class SimpleAnimation;

	class Transform:
		protected Updatable
	{
	public:
		/* Transform entity 
			@return Time left, that transform did not consume.
		*/
		sf::Time virtual		Apply(sf::Time _time, CMaker::SimpleAnimation* _entity) = 0;

		void					Reset();

								Transform(sf::Time _length);
		virtual					~Transform();

	protected:
		sf::Time				getLength();

	private:
		const sf::Time			length;
	};

}