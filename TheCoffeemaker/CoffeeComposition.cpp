#include "CoffeeComposition.h"

#include <algorithm>

namespace CMaker {

	CoffeeComposition::CoffeeComposition()
	{
	}

	CoffeeComposition::CoffeeComposition(const CoffeeComposition & _comp)
	{
		elements = _comp.elements;
	}

	CoffeeComposition::~CoffeeComposition()
	{
	}

	CoffeeComposition CoffeeComposition::operator=(const CoffeeComposition & _comp)
	{
		elements = _comp.elements;

		return *this;
	}

	CoffeeComposition CoffeeComposition::operator+=(CoffeeComponent _component)
	{
		elements.push_back(_component);

		return *this;
	}

	CoffeeComposition CoffeeComposition::operator-=(CoffeeComponent _component)
	{
		auto it = std::find(elements.begin(), elements.end(), _component);
		if ( it != elements.end()) {
			elements.erase(it);
		};

		return *this;
	}

	bool CoffeeComposition::operator==(const CoffeeComposition& _component)
	{
		CoffeeComposition tmpComposition(*this);

		for(auto lComp : _component.elements){
			if ( tmpComposition.haveComponent(lComp) ) {
				tmpComposition -= lComp;
			}
			else {
				return false;
			}
		}

		if (tmpComposition.getComponentCount() == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	int CoffeeComposition::getComponentCount()
	{
		return elements.size();
	}

	bool CoffeeComposition::haveComponent(CoffeeComponent _component)
	{
		return ( std::find(elements.begin(), elements.end(), _component) != elements.end());
	}

}