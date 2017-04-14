#include "Unit.h"

#include <TheCoffeeMaker/ResourceManager.h>

namespace CMaker {

	/*
		Constructor / Destructor
	*/
	Unit::Unit():
		enumTexture{ CMaker::Texture::NONE }
	{
		setPosition(sf::Vector2f(0.f, 0.f));
		loadTexture(); 
	}

	Unit::Unit(CMaker::Texture _enumTexture, sf::Vector2f _pos):
		enumTexture{ _enumTexture }
	{
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
		setTexture(ResourceMgr.getResource(this->enumTexture));
	}

	/* Set visibility */
	void Unit::Show(bool _show)
	{
		visible = _show;
	}

}