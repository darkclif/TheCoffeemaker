#pragma once
#include <map>
#include <vector>

namespace CMaker {

	enum class CoffeeComponent {
		MILK,
		FOAMED_MILK,
		SUGAR,
		ESPRESSO,
		CINAMON,
		WATER,
		COCOA
	};

	class CoffeeComposition
	{
	public:
		CoffeeComposition operator=(const CoffeeComposition& _comp);
		bool operator==(const CoffeeComposition& _component);

		CoffeeComposition operator+=(CoffeeComponent _component);
		CoffeeComposition operator-=(CoffeeComponent _component);

		int getComponentCount();
		bool haveComponent(CoffeeComponent _component);

		CoffeeComposition();
		CoffeeComposition(const CoffeeComposition& _comp);
		~CoffeeComposition();
		
	private:
		std::vector<CoffeeComponent> elements;

	};

}