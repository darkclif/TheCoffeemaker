#include "HeatBar.h"

namespace CMaker {
	void HeatBar::setHeat(sf::Uint8 _heat)
	{
		if ( _heat <= MAX_BARS && _heat >= 1 ) {
			heat = _heat;
			setHeatRect();
		}
	}

	void HeatBar::setHeatRect()
	{
		static const sf::Vector2i heatRectSize(3,11);

		static const std::vector<sf::IntRect> heatRects = {
			{ 0, 0, heatRectSize.x, heatRectSize.y },
			{ 3, 0, heatRectSize.x, heatRectSize.y },
			{ 6, 0, heatRectSize.x, heatRectSize.y },

			{ 9, 0, heatRectSize.x, heatRectSize.y },
			{ 12, 0, heatRectSize.x, heatRectSize.y },
			{ 15, 0, heatRectSize.x, heatRectSize.y },

			{ 18, 0, heatRectSize.x, heatRectSize.y },
			{ 21, 0, heatRectSize.x, heatRectSize.y },
			{ 24, 0, heatRectSize.x, heatRectSize.y },
		};

		setTextureRect(heatRects[heat-1]);
	}

	HeatBar::HeatBar(sf::Vector2f _pos, sf::Uint8 _heat):
		Unit(Texture::HEAT_BAR, _pos),
		heat{_heat}
	{
		setHeatRect();
	}

	HeatBar::~HeatBar()
	{

	}

}	