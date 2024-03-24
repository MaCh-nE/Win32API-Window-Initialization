#include<iostream>
#include<Windows.h>
#include<Game.h>


int main() {
	try {
		Game game;
		game.run();
	}
	catch (const char* str) {
		std::cout << str << std::endl;
	}
}