#pragma once
#include <TheCoffeeMaker/Animation.h>

namespace CMaker {

	class Customer:
		public Animation
	{
	public:
		void		Update(sf::Time _time) override;				
		
					Customer(sf::Vector2f _pos, int _cusId);
					~Customer();

	private:
		static const std::vector<sf::IntRect> customersRect;

		std::string coffeeName;
	};

}