#pragma once
#include <vector>

#include <TheCoffeeMaker/Coffee.h>
#include <TheCoffeeMaker/CoffeeComposition.h>

namespace CMaker {

	/* Coffee types */
	enum class CoffeeType : int {
		ESPRESSO = 0,
		LATTE,
		CAPPUCINO,
		AMERICANO,

		_SIZE
	};

	#define CoffeeJudgeInst CoffeeJudge::getInstance()

	class CoffeeJudge
	{
	public:
		/* Singleton */
		static CoffeeJudge& getInstance() {
			static CoffeeJudge instance;

			return instance;
		}

		/* Get coffee composition pattern */
		const CoffeeComposition& getCoffeeComposition(CoffeeType _type);

		/* Convert coffee type to string */
		static const std::vector<std::string> CoffeeTypeToString;

		/* Score details */
		struct OrderScore {
			OrderScore() : score(0), what(0) {}

			enum class What : int {
				NO_SUGAR = 1,
				BAD_COMPONENT_QUANTITY = 1 << 1,
				BAD_COFFEES_QUANTITY = 1 << 2,
				BAD_COFFEES_TYPE = 1 << 3
			};

			int score;
			int what;

			/* Set what happend */
			void raiseWhat(What _what) {
				what = what | ((int)_what);
			}
			void hideWhat(What _what) {
				what = what & ~((int)_what);
			}
			bool isWhat(What _what) {
				return what & ((int)_what);
			}
		};

		/* Score constans */
		static const int COFFEE_TYPE_MATCH = 10;
		static const int COFFEE_QUANTITY_MATCH = 10;

		/* Count coffee group score based on customer expectations */
		OrderScore countCoffeeScore(const Coffee& _coffeeGiven, const CoffeeComposition& _coffeeExp) const;

	private:
		/* Coffee type patterns */
		std::map<CoffeeType, CoffeeComposition> mapCoffeePatterns;

		/* Coffee creators */
		template<CoffeeType Type>
		CoffeeComposition getCoffeePatern() {
			throw std::exception("CoffeePatern not implemented.");
		}

		template<>
		CoffeeComposition getCoffeePatern<CoffeeType::ESPRESSO>() {
			CoffeeComposition lComposition;

			lComposition += CoffeeComponent::ESPRESSO;

			return lComposition;
		}

		template<>
		CoffeeComposition getCoffeePatern<CoffeeType::LATTE>() {
			CoffeeComposition lComposition;

			lComposition += CoffeeComponent::ESPRESSO;
			lComposition += CoffeeComponent::FOAMED_MILK;
			lComposition += CoffeeComponent::FOAMED_MILK;

			return lComposition;
		}

		template<>
		CoffeeComposition getCoffeePatern<CoffeeType::CAPPUCINO>() {
			CoffeeComposition lComposition;

			lComposition += CoffeeComponent::ESPRESSO;
			lComposition += CoffeeComponent::FOAMED_MILK;
			lComposition += CoffeeComponent::FOAMED_MILK;
			lComposition += CoffeeComponent::COCOA;

			return lComposition;
		}

		template<>
		CoffeeComposition getCoffeePatern<CoffeeType::AMERICANO>() {
			CoffeeComposition lComposition;

			lComposition += CoffeeComponent::ESPRESSO;
			lComposition += CoffeeComponent::WATER;
			lComposition += CoffeeComponent::WATER;

			return lComposition;
		}

		/* Constructor / Destructor */
		CoffeeJudge();
		~CoffeeJudge();

		/* Singleton */
		CoffeeJudge(const CoffeeJudge&) = delete;
		CoffeeJudge operator=(const CoffeeJudge&) = delete;
	};

}