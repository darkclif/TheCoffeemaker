#include "Bin.h"

namespace CMaker {

	void Bin::setOpen(bool _open)
	{
		open = _open;
		setBinRect();
	}

	void Bin::setBinRect()
	{
		static const sf::Vector2i binRectSize(23, 35);

		static const std::vector<sf::IntRect> heatRects = {
			{ 0, 0, binRectSize.x, binRectSize.y },
			{ 23, 0, binRectSize.x, binRectSize.y }
		};

		setTextureRect(heatRects[open ? 1 : 0]);
	}

	Bin::Bin(sf::Vector2f _pos):
		Unit(Texture::BIN, _pos)
	{
		setBinRect();
		setOriginAlign(OriginAlign::TOP_LEFT);
		setScale(sf::Vector2f(4.f, 4.f));
	}

	Bin::~Bin()
	{

	}

}