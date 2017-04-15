#pragma once
#include <SFML/Graphics.hpp>

#include <TheCoffeeMaker/TextureResManager.h>

namespace CMaker {

	class Unit: 
		public sf::Sprite
	{
	public:
		enum class OriginAlign {
			TOP_LEFT, TOP_CENTER, TOP_RIGHT,
			MIDDLE_LEFT, MIDDLE_CENTER, MIDDLE_RIGHT,
			BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT
		};

	public:
		void virtual		Draw(sf::RenderWindow& _render);

		/* Set origin of sprite */
		void				setOriginAlign(OriginAlign _align = OriginAlign::MIDDLE_CENTER);

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