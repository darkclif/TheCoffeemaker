// Bubus - The Coffeemaker (2017)
//
// Game by Maciej Wydro (Fo3)

#include <string>
#include <stdio.h>

#include <TheCoffeeMaker/Game.h>

const std::string VERSION = "0.0.1 Alpha";

int main() {
	printf("Bubus - The Coffeemaker. ver. %s\n", VERSION);
	
	CMaker::Game GameEngine;
	GameEngine.Run();

	return 0;
}