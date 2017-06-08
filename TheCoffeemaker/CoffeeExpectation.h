#pragma once
#include <vector>

class CoffeeExpectation
{
public:

	enum class TopingType {
		SUGAR
	};

	struct Toping {
		TopingType type;
		int count;
	};

	CoffeeExpectation();
	~CoffeeExpectation();

private:
	CoffeeType				type;
	std::vector<Toping>		topings;
};