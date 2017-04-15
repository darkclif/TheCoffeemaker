#include "transLabel.h"

namespace CMaker {
	sf::Time transLabel::Apply(sf::Time _time, CMaker::SimpleAnimation * _entity)
	{
		return _time;
	}

	int transLabel::getLabel()
	{
		return label;
	}

	transLabel::transLabel(int _label):
		label{ _label }
	{

	}

	transLabel::~transLabel()
	{

	}

}