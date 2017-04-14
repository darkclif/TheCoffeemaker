#pragma once
#include <SFML/Graphics.hpp>

#include <TheCoffeeMaker/TextureResManager.h>

namespace CMaker {

	class Unit: 
		public sf::Sprite
	{
	public:
		void virtual		Draw(sf::RenderWindow& _render);

							Unit();
							Unit(CMaker::Texture _enumTexture, sf::Vector2f _pos);
		virtual				~Unit();
	
		bool				isVisible();

	protected:
		void				setTextureEnum(CMaker::Texture _enumTexture);
		CMaker::Texture		getTextureEnum();

		void				Show(bool _show);

	private:
		using				sf::Sprite::setTexture; /* Make this function private, change inherited (protected) access */
		void				loadTexture();

		bool				visible;
		CMaker::Texture		enumTexture;
	};

}