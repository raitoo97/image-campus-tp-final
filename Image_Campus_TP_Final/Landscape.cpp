#include "Landscape.h"
Landscape::Landscape()
{
	sprite_sky = new sf::Sprite;
	texture_sky = new sf::Texture;
	texture_box = new sf::Texture;
	sprite_box = new sf::Sprite;
	texture_river = new sf::Texture;
	sprite_river = new sf::Sprite;
	sprite_river2 = new sf::Sprite;
	sprite_river3 = new sf::Sprite;
	sprite_river4 = new sf::Sprite;
	sprite_river5 = new sf::Sprite;
	black_layer = new sf::RectangleShape({ 1920,1080 });
	size_river = 175.f;
	//Landscape
	if (!texture_sky->loadFromFile("../assets/Landscape.png"))
	{
		cout << "fail" << endl;
	}
	sprite_sky->setTexture(*texture_sky);
	sprite_sky->setScale(1920.f / texture_sky->getSize().x, 1080.f / texture_sky->getSize().y);
	//Box
	if (!texture_box->loadFromFile("../assets/Box.png"))
	{
		cout << "fail" << endl;
	}
	sprite_box->setTexture(*texture_box);
	sprite_box->setScale(50.f / texture_box->getSize().x, 50.f / texture_box->getSize().y);
	sprite_box->setPosition(150.f, 173.f);
	//river texture
	if (!texture_river->loadFromFile("../assets/river.png"))
	{
		cout << "fail" << endl;
	}
	sprite_river->setTexture(*texture_river);
	sprite_river->setScale(size_river / texture_river->getSize().x, size_river / texture_river->getSize().y);
	sprite_river->setPosition(920.f,573.f);
	//river2
	sprite_river2->setTexture(*texture_river);
	sprite_river2->setScale(size_river / texture_river->getSize().x, size_river / texture_river->getSize().y);
	sprite_river2->setPosition(500.f, 200.f);
	//river3
	sprite_river3->setTexture(*texture_river);
	sprite_river3->setScale(size_river / texture_river->getSize().x, size_river / texture_river->getSize().y);
	sprite_river3->setPosition(1350.f, 200.f);
	//river4
	sprite_river4->setTexture(*texture_river);
	sprite_river4->setScale(size_river / texture_river->getSize().x, size_river / texture_river->getSize().y);
	sprite_river4->setPosition(338.f, 700.f);
	//river5
	sprite_river5->setTexture(*texture_river);
	sprite_river5->setScale(size_river / texture_river->getSize().x, size_river / texture_river->getSize().y);
	sprite_river5->setPosition(1619.f, 700.f);
	//layer_black
	black_layer->setFillColor(sf::Color::Color(0, 0, 0, 150));
}
Landscape::~Landscape()
{
	cout << "~Landscape()" << endl;
	delete sprite_sky;
	delete texture_sky;
	delete sprite_box;
	delete texture_box;
	delete texture_river;
	delete sprite_river;
	delete sprite_river2;
	delete sprite_river3;
	delete sprite_river4;
	delete sprite_river5;
	delete black_layer;
}
sf::Sprite* Landscape::get_sky() const
{
	return sprite_sky;
}
sf::Sprite* Landscape::get_box()const
{
	return sprite_box;
}
sf::Sprite* Landscape::get_river()const
{
	return sprite_river;
}
sf::Sprite* Landscape::get_river_2() const
{
	return sprite_river2;
}
sf::Sprite* Landscape::get_river_3() const
{
	return sprite_river3;
}
sf::Sprite* Landscape::get_river_4() const
{
	return sprite_river4;
}
sf::Sprite* Landscape::get_river_5() const
{
	return sprite_river5;
}
sf::RectangleShape* Landscape::get_layer() const
{
	return black_layer;
}


