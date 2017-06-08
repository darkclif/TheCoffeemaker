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
		COCOA,

		_SIZE
	};

	class CoffeeComposition
	{
	public:
		CoffeeComposition operator=(const CoffeeComposition& _comp);
		bool operator==(const CoffeeComposition& _component) const;

		CoffeeComposition operator+=(CoffeeComponent _component);
		CoffeeComposition operator-=(CoffeeComponent _component);

		/* Convert coffee type to string */
		static const std::vector<std::string> CoffeeComponentToString;

		int getComponentCount();
		bool haveComponent(CoffeeComponent _component);

		CoffeeComposition();
		CoffeeComposition(const CoffeeComposition& _comp);
		~CoffeeComposition();
		
	private:
		std::vector<CoffeeComponent> elements;

	};

}