#pragma once
#include <iostream>
#include "Enemie.h"
#include "Character.h"
#include "Landscape.h"
#include <SFML/Graphics.hpp>

using std::cout;
using std::endl;

class Enemie
{
private:
	sf::Sprite* sprite;
	sf::Texture* texture;
	float life = 0;
	float damage = 0;
	//enemie movement
	float speed_enemie;
	float lenght_vector;
	float normalized_x;
	float normalized_y;
	float x_vector;
	float y_vector;
public:
	Enemie(float life, float damage, float posicionx = 0.f , float posiciony = 0.f);
	virtual ~Enemie();
	sf::Sprite* get_enemie()const;
	float get_life() const;
	float get_damage() const;
	void set_life(float life);
	void set_damage(float damage);
	void recibe_damage(float damage);
	void enemy_change_color(std::vector<Enemie*>x, sf::Clock* clock, sf::Time* time, Landscape* reflevel);
	void ia_controller(Character* target, std::vector<Enemie*>x, sf::Clock* clock, sf::Time* time,float damage);
};

