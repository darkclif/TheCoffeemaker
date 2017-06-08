#pragma once
#include <vector>

#include <TheCoffeeMaker/Coffee.h>
#include <TheCoffeeMaker/CoffeeComposition.h>

namespace CMaker {

	#define CoffeeJudgeInst CoffeeJudge::getInstance()

	class CoffeeJudge
	{
	public:
		/* Singleton */
		CoffeeJudge& getInstance() {
			static CoffeeJudge instance;

			return instance;
		}

		/* Coffee types */
		enum class CoffeeType {
			ESPRESSO,
			LATTE,
			CAPPUCINO,
			AMERICANO
		};

		/* Coffee type patterns */
		std::map<CoffeeType, CoffeeComposition> CoffeeTypePatterns;

		template<CoffeeType Type>
		const CoffeeComposition& getCoffeePatern() {
			throw std::exception("CoffeePatern not implemented.");
		}

		template<>
		const CoffeeComposition& getCoffeePatern<CoffeeType::ESPRESSO>() {
			auto it = CoffeeTypePatterns.find(CoffeeType::ESPRESSO);

			if (it != CoffeeTypePatterns.end()) {
				return it->second;
			}
			else {
				CoffeeComposition lComposition;

				lComposition += CoffeeComponent::ESPRESSO;

				CoffeeTypePatterns.insert(std::make_pair(CoffeeType::ESPRESSO, lComposition));
			}
		}

		template<>
		const CoffeeComposition& getCoffeePatern<CoffeeType::LATTE>() {
			auto it = CoffeeTypePatterns.find(CoffeeType::LATTE);

			if (it != CoffeeTypePatterns.end()) {
				return it->second;
			}
			else {
				CoffeeComposition lComposition;

				lComposition += CoffeeComponent::ESPRESSO;
				lComposition += CoffeeComponent::FOAMED_MILK;
				lComposition += CoffeeComponent::FOAMED_MILK;

				CoffeeTypePatterns.insert(std::make_pair(CoffeeType::LATTE, lComposition));
			}
		}

		template<>
		const CoffeeComposition& getCoffeePatern<CoffeeType::CAPPUCINO>() {
			auto it = CoffeeTypePatterns.find(CoffeeType::CAPPUCINO);

			if (it != CoffeeTypePatterns.end()) {
				return it->second;
			}
			else {
				CoffeeComposition lComposition;

				lComposition += CoffeeComponent::ESPRESSO;
				lComposition += CoffeeComponent::FOAMED_MILK;
				lComposition += CoffeeComponent::FOAMED_MILK;
				lComposition += CoffeeComponent::COCOA;

				CoffeeTypePatterns.insert(std::make_pair(CoffeeType::CAPPUCINO, lComposition));
			}
		}

		template<>
		const CoffeeComposition& getCoffeePatern<CoffeeType::AMERICANO>() {
			auto it = CoffeeTypePatterns.find(CoffeeType::AMERICANO);

			if (it != CoffeeTypePatterns.end()) {
				return it->second;
			}
			else {
				CoffeeComposition lComposition;

				lComposition += CoffeeComponent::ESPRESSO;
				lComposition += CoffeeComponent::WATER;
				lComposition += CoffeeComponent::WATER;

				CoffeeTypePatterns.insert(std::make_pair(CoffeeType::AMERICANO, lComposition));
			}
		}

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
		CoffeeJudge();
		~CoffeeJudge();

		CoffeeJudge(const CoffeeJudge&) = delete;
		CoffeeJudge operator=(const CoffeeJudge&) = delete;
	};

}