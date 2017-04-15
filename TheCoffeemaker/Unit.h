#pragma once
#include <SFML/Graphics.hpp>

#include <TheCoffeeMaker/TextureResManager.h>
#include <TheCoffeeMaker/Drawable.h>

namespace CMaker {

	class Unit: 
		public sf::Sprite,
		public CMaker::Drawable
	{
	public:
		/* Enum for change sf::Sprite origin automagicaly */
		enum class OriginAlign {
			TOP_LEFT, TOP_CENTER, TOP_RIGHT,
			MIDDLE_LEFT, MIDDLE_CENTER, MIDDLE_RIGHT,
			BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT
		};

	public:
		/* Basic draw, just show the sprite */
		void virtual		Draw(sf::RenderWindow& _render) override;

		/* Set origin of sprite */
		void				setOriginAlign(OriginAlign _align = OriginAlign::MIDDLE_CENTER);

		/* Set color alpha */
		void				setColorAlpha(sf::Uint8 _alpha);
	
		/* Check visibility */
		bool				isVisible();

		/* Constructor / Destructor */
							Unit();
							Unit(CMaker::Texture _enumTexture, sf::Vector2f _pos);
		virtual				~Unit();

	protected:
		/* Change unit texture */
		void				setTextureEnum(CMaker::Texture _enumTexture);
		CMaker::Texture		getTextureEnum();

		/* Change unit visibilty */
		void				Show(bool _show);

	private:
		/* Make this function private, change inherited (protected) access */
		using				sf::Sprite::setTexture; 

		/* Load texture from ResourcesManager */
		void				loadTexture();

		bool				visible;
		CMaker::Texture		enumTexture;
	};

}