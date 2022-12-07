#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "MainMenu.h"
#include <string>

using std::endl;
using std::cout;

int main() {
		MainMenu menu;
		if (menu.init_menu()) {
			menu.loop_menu();
		}
		menu.stop_menu();
		Game game;
		if (game.init()) {
			game.loop();
		}
		game.stop();
}
