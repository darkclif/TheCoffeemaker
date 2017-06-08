#include "CoffeeJudge.h"

namespace CMaker {

	const std::vector<std::string> CoffeeJudge::CoffeeTypeToString = {
		"Espresso",
		"Latte",
		"Cappucino",
		"Americano"
	};

	const CoffeeComposition & CoffeeJudge::getCoffeeComposition(CoffeeType _type)
	{
		return mapCoffeePatterns.at(_type);
	}

	CoffeeJudge::OrderScore CoffeeJudge::countCoffeeScore(const Coffee& _coffeeGiven, const CoffeeComposition& _coffeeExp) const
	{
		OrderScore orderScore;

		if ( _coffeeGiven.getComposition() == _coffeeExp ) {
			orderScore.score = COFFEE_QUANTITY_MATCH + COFFEE_TYPE_MATCH;
		}
		else {
			orderScore.score = 5;
			orderScore.raiseWhat(CoffeeJudge::OrderScore::What::BAD_COFFEES_TYPE);
		}
		
		return orderScore;
	}

	CoffeeJudge::CoffeeJudge()
	{
		mapCoffeePatterns.insert(std::make_pair(CoffeeType::AMERICANO, getCoffeePatern<CoffeeType::AMERICANO>()));
		mapCoffeePatterns.insert(std::make_pair(CoffeeType::CAPPUCINO, getCoffeePatern<CoffeeType::CAPPUCINO>()));
		mapCoffeePatterns.insert(std::make_pair(CoffeeType::ESPRESSO, getCoffeePatern<CoffeeType::ESPRESSO>()));
		mapCoffeePatterns.insert(std::make_pair(CoffeeType::LATTE, getCoffeePatern<CoffeeType::LATTE>()));
	}

	CoffeeJudge::~CoffeeJudge()
	{
	}

}