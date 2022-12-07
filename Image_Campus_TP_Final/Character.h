#pragma once
#include <iostream>
#include "Landscape.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using std::cout;
using std::endl;

constexpr int LIFE = 2000;
constexpr float DAMAGE = .4f;
constexpr int WIDTH_SCREEN = 1920;
constexpr int HEIGHT_SCREEN = 1080;

class Character
{
private:
	sf::Sprite* sprite;
	sf::Texture* texture;
	sf::Event* pj_events;
	sf::SoundBuffer buffer_reduce_speed;
	sf::Sound sound_reduce_speed;
	int life;
	float damage;
	float move_speed;
	float reduce_speed;
	//movesprite
	int divide_sprite_x;
	int divide_sprite_y;
public:
	Character();
	virtual ~Character();
	//getters
	sf::Sprite* get_character()const;
	int get_life() const;
	float get_damage() const;
	sf::Sound get_sound() const;
	//setters
	void set_life(int life);
	void set_damage(float damage);
	//functions
	void recibe_damage(float damage);
	void collisions(Landscape* landscape_ref);
	void set_frame(sf::Sprite* ref, sf::Vector2i number_frames);
	void inputs(sf::RenderWindow* ref_window, std::vector<sf::Clock*>clock, std::vector<sf::Time*>time);
};

