// Bubus - The Coffeemaker (2017)
//
// Game by Maciej Wydro (Fo3)

#include <string>
#include <iostream>

#include <TheCoffeeMaker/Game.h>

const std::string VERSION = "0.0.1 Alpha";

int main() {
	std::cout << "Bubus - The Coffeemaker. ver. " << VERSION << std::endl;
	
	CMaker::Game GameEngine;
	GameEngine.Run();

	return 0;
}