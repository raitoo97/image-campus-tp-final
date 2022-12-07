#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using std::cout;
using std::endl;

class Landscape
{
private:
	//landscape
	sf::Texture* texture_sky;
	sf::Sprite* sprite_sky;
	//box
    sf::Texture* texture_box;
	sf::Sprite* sprite_box;
	//rivers
	sf::Texture* texture_river;
	sf::Sprite* sprite_river;
	sf::Sprite* sprite_river2;
	sf::Sprite* sprite_river3;
	sf::Sprite* sprite_river4;
	sf::Sprite* sprite_river5;
	float size_river;
	//black layer
	sf::RectangleShape* black_layer;
public:
	Landscape();
	~Landscape();
	sf::Sprite* get_sky() const;
	sf::Sprite* get_box() const;
	sf::Sprite* get_river() const;
	sf::Sprite* get_river_2() const;
	sf::Sprite* get_river_3() const;
	sf::Sprite* get_river_4() const;
	sf::Sprite* get_river_5() const;
	sf::RectangleShape* get_layer() const;
};

