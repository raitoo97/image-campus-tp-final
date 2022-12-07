#pragma once
#include <iostream>
#include "Character.h"
#include "Landscape.h"
#include "Enemie.h"
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using std::srand;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector;

constexpr float TIME_TO_SPAWN = 1.f;

constexpr float ENEMY_LIFE = 50;
constexpr float ENEMY_DAMAGE = 1.f;

constexpr float MOUSEX_MARGEN= -30.f;
constexpr float MOUSEY_MARGEN = -30.f;

const string TITLE = "DragonLegacy";

class Game
{
private:
	bool game_over;
	sf::Event* event;
	Character* dragon;
	vector <Enemie*> enemie;
	sf::RenderWindow* window;
	Landscape* landscape;
	//explosion frames
	sf::Vector2i current_frame;
	bool show_eplosion;
	//score
	int kills;
	//texts and fonts
	sf::Text text_life;
	sf::Text text_score;
	sf::Text text_escape;
	sf::Font font_life;
	//Mouse
	sf::Vector2i mouse_pos;
	//textures and sprites
	sf::Texture* t_gun_sight;
	sf::Sprite* s_gun_sight;
	sf::Texture* t_explosion;
	sf::Sprite* s_explosion;
	//sounds
	sf::Music music;
	sf::Music music_zombie;
	sf::Music sound_explosion;
	//times
	sf::Clock* clock_sound_explosion;
	sf::Time* time_sound_explosion;
	sf::Clock* clock_action;
	sf::Time* time_action;
	sf::Clock* clock_spawn;
	sf::Time* time_spawn;
	sf::Clock* clock_change_color;
	sf::Time* time_change_color;
	sf::Clock* clock_scape;
	sf::Time* time_scape;
	std::vector<sf::Clock*>clocks_move_pj;
	std::vector<sf::Time*>times_move_pj;
	//enmies spawn
	int rand_num;
	float poision_x;
	float posicion_Y;
	//final screen
	sf::RectangleShape* layer_final;
public:
	Game();
	virtual ~Game();
	bool init();
	void loop();
	void stop();
	void dragon_atack();
	void drawing();
	void spawn_enemies();
	void explosions_frame(sf::Sprite* ref, sf::Vector2i number_frames);
};

