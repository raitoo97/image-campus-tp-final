#pragma once
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#define MAX_SIZE_BOTTONS 3
#define MAX_SIZE_TUTORIAL 2

using std::cout;
using std::endl;
using std::string;

constexpr float WIDTH_SCREEN_MENU = 1920.f;
constexpr float HEIGHT_SCREEN_MENU = 1080.f;
const string TITLE_TITLE= "DragonLegacy";
constexpr float MOUSEX_MARGEN_MENU = -30.f;
constexpr float MOUSEY_MARGEN_MENU = -30.f;

class MainMenu
{
private:
	//classes
	sf::RenderWindow* window_menu;
	sf::Event* event_menu;
	//gun_sight
	sf::Texture t_menu_gun_sight;
	sf::Sprite s_menu_gun_sight;
	//wallpaper
	sf::Texture t_menu;
	sf::Sprite s_menu;
	//mouse sprite tutorial
	sf::Texture mouse_menu_t;
	sf::Sprite mouse_menu_s;
	sf::Texture wasd_menu_t;
	sf::Sprite wasd_menu_s;
	//texts and fonts
	sf::Font font_menu;
	sf::Font font_tutorial;
	sf::Text texts_menu[MAX_SIZE_BOTTONS];
	sf::Text text_wasd_mouse[MAX_SIZE_TUTORIAL];
	//music
	sf::Music* music_menu;
	//mouse posicion
	sf::Vector2i mouse_pos_menu;
public:
	MainMenu();
	virtual ~MainMenu();
	bool init_menu();
	void loop_menu();
	void stop_menu();
	void input_menu();
	void drawing_menu();
	void collision_menu();
};

