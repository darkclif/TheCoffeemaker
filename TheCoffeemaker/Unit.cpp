#include "Unit.h"

#include <TheCoffeeMaker/ResourceManager.h>

namespace CMaker {

	/*
		Constructor / Destructor
	*/
	void Unit::setColorAlpha(sf::Uint8 _alpha)
	{
		sf::Color color = getColor();
		color.a = _alpha;
		setColor(color);
	}

	Unit::Unit():
		enumTexture{ CMaker::Texture::NONE }
	{
		originAlign = OriginAlign::TOP_LEFT;
		setPosition(sf::Vector2f(0.f, 0.f));
		loadTexture(); 
	}

	Unit::Unit(CMaker::Texture _enumTexture, sf::Vector2f _pos):
		enumTexture{ _enumTexture }
	{
		originAlign = OriginAlign::TOP_LEFT;
		setPosition(_pos);
		loadTexture();
	}

	Unit::~Unit()
	{
	}

	bool Unit::isVisible()
	{
		return visible;
	}

	void Unit::setToDelete(bool _delete)
	{
		toDelete = _delete;
	}

	bool Unit::isToDelete()
	{
		return toDelete;
	}

	void Unit::setOriginAlign(OriginAlign _align)
	{
		sf::FloatRect lRect = getLocalBounds();
		sf::Vector2f lOrig;

		originAlign = _align;

		switch (_align) {
			case OriginAlign::TOP_LEFT: lOrig = sf::Vector2f(0.f, 0.f); break;
			case OriginAlign::TOP_CENTER: lOrig = sf::Vector2f(lRect.width / 2.f, 0.f); break;
			case OriginAlign::TOP_RIGHT: lOrig = sf::Vector2f(lRect.width, 0.f); break;

			case OriginAlign::MIDDLE_LEFT: lOrig = sf::Vector2f(0.f, lRect.height / 2.f); break;
			case OriginAlign::MIDDLE_CENTER: lOrig = sf::Vector2f(lRect.width / 2.f, lRect.height / 2.f); break;
			case OriginAlign::MIDDLE_RIGHT: lOrig = sf::Vector2f(lRect.width, lRect.height / 2.f); break;

			case OriginAlign::BOTTOM_LEFT: lOrig = sf::Vector2f(0.f, lRect.height); break;
			case OriginAlign::BOTTOM_CENTER: lOrig = sf::Vector2f(lRect.width / 2.f, lRect.height); break;
			case OriginAlign::BOTTOM_RIGHT: lOrig = sf::Vector2f(lRect.width, lRect.height); break;
			default: break;
		}

		setOrigin(lOrig);
	}

	OriginAlign Unit::getOriginAlign()
	{
		return originAlign;
	}

	void Unit::fitRenderView(sf::RenderWindow& _render)
	{
		sf::Vector2f lSize = _render.getView().getSize();
		setScale(lSize.x / getLocalBounds().width, lSize.y / getLocalBounds().height);	
	}

	void Unit::Draw(sf::RenderWindow & _render)
	{
		_render.draw(*this);
	}

	/*
		Access texture and set texture enum
	*/
	void Unit::setTextureEnum(CMaker::Texture _enumTexture)
	{
		enumTexture = _enumTexture;
		loadTexture();
	}

	CMaker::Texture Unit::getTextureEnum()
	{
		return enumTexture;
	}

	/* Load texture from ResourceManager */
	void Unit::loadTexture()
	{
		setTexture(ResourceMgr.getResource(this->enumTexture), true);
	}

	/* Set visibility */
	void Unit::setVisible(bool _show)
	{
		visible = _show;
	}

}