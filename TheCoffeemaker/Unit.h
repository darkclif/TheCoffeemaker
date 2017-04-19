#pragma once
#include <SFML/Graphics.hpp>

#include <TheCoffeeMaker/TextureResManager.h>
#include <TheCoffeeMaker/Drawable.h>

namespace CMaker {
	/* Enum for change sf::Sprite origin automagicaly */
	enum class OriginAlign {
		TOP_LEFT, TOP_CENTER, TOP_RIGHT,
		MIDDLE_LEFT, MIDDLE_CENTER, MIDDLE_RIGHT,
		BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT
	};

	/* Unit class */
	class Unit: 
		public sf::Sprite,
		public CMaker::Drawable
	{
	public:
		/* Basic draw, just show the sprite */
		void virtual		Draw(sf::RenderWindow& _render) override;

		/* Set origin of sprite */
		void				setOriginAlign(OriginAlign _align = OriginAlign::MIDDLE_CENTER);

		/* Get origin align */
		OriginAlign			getOriginAlign();

		/* Resize unit sprite to fit the whole window */
		void				fitRenderView(sf::RenderWindow& _render);

		/* Set color alpha */
		void				setColorAlpha(sf::Uint8 _alpha);
		
		/* Change unit texture */
		void				setTextureEnum(CMaker::Texture _enumTexture);
		CMaker::Texture		getTextureEnum();

		/* Change unit visibilty */
		void				setVisible(bool _show);
		bool				isVisible();

		/* Change delete indicator */
		void				setToDelete(bool _delete);
		bool				isToDelete();

		/* Constructor / Destructor */
							Unit();
							Unit(CMaker::Texture _enumTexture, sf::Vector2f _pos);
		virtual				~Unit();

	private:
		/* Make this function private, change inherited (protected) access */
		using				sf::Sprite::setTexture; 

		/* Load texture from ResourcesManager */
		void				loadTexture();

		/* Indicate that this unit should be deleted

			This should be used by queues containing this unit.
		*/
		bool				toDelete;

		/* TODO: NOT_USED: If unit should be rendered */
		bool				visible;
		
		/* My enum for textures */
		CMaker::Texture		enumTexture;
		
		/* How unit origin should be aligned */
		OriginAlign			originAlign;
	};

}