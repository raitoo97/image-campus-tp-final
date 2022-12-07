#include "Enemie.h"
Enemie::Enemie(float life, float damage, float posicionx, float posiciony)
{
	this->life = life;
	this->damage = damage;
	sprite = new sf::Sprite;
	texture = new sf::Texture;
    speed_enemie =.2f;
    lenght_vector = 0.f;
    normalized_x = .0f;
    normalized_y = .0f;
    x_vector = .0f;
    y_vector = .0f;
	if (!texture->loadFromFile("../assets/enemie.png"))
	{
		cout << "fail" << endl;
	}
	sprite->setTexture(*texture);
	sprite->setOrigin(texture->getSize().x * 0.5f, texture->getSize().y * 0.5f);
	sprite->setPosition(posicionx, posiciony);
	sprite->setScale(100.f / texture->getSize().x, 100.f / texture->getSize().y);
}
Enemie::~Enemie()
{
	cout << "~Enemie()" << endl;
	delete sprite;
	delete texture;
}
sf::Sprite* Enemie::get_enemie() const
{
	return sprite;
}
float Enemie::get_life() const
{
	return life;
}
float Enemie::get_damage() const
{
	return damage;
}
void Enemie::set_life(float life)
{
	this->life = life;
}
void Enemie::set_damage(float damage)
{
	this->damage = damage;
}
void Enemie::recibe_damage(float damage)
{
	life -= damage;
}
void Enemie::enemy_change_color(std::vector<Enemie*>x, sf::Clock* clock, sf::Time* time, Landscape* reflevel)
{
  	if (time->asSeconds() > .2f) {
		for (int i = 0; i < x.size(); i++) {
			if (x[i]->get_enemie()->getGlobalBounds().intersects(reflevel->get_sky()->getGlobalBounds())) {
				x[i]->get_enemie()->setColor(sf::Color::Color(255,255,255,255));
				clock->restart();
			}
		}
	}
}
void Enemie::ia_controller(Character* target, std::vector<Enemie*>x, sf::Clock* clock, sf::Time* time, float damage)
{
    for (int i = 0; i < x.size(); i++) {
        //atack
        if (target->get_character()->getGlobalBounds().intersects(x[i]->get_enemie()->getGlobalBounds())) {
            target->get_character()->setColor(sf::Color::Red);
            target->recibe_damage(damage);
        }
        //screen collisions
        if (x[i]->get_enemie()->getPosition().x < 0.0f) {
            x[i]->get_enemie()->setPosition(0.f, x[i]->get_enemie()->getPosition().y);
        }
        else if (x[i]->get_enemie()->getPosition().x >= WIDTH_SCREEN) {
            x[i]->get_enemie()->setPosition(WIDTH_SCREEN, x[i]->get_enemie()->getPosition().y);
        }
        else if (x[i]->get_enemie()->getPosition().y < 0.0f) {
            x[i]->get_enemie()->setPosition(x[i]->get_enemie()->getPosition().x, .0f);
        }
        else if (x[i]->get_enemie()->getPosition().y >= HEIGHT_SCREEN) {
            x[i]->get_enemie()->setPosition(x[i]->get_enemie()->getPosition().x, HEIGHT_SCREEN);
        }
        // MOVEMENT
        if (time->asSeconds() > .2f) {
            x_vector = target->get_character()->getPosition().x - x[i]->get_enemie()->getPosition().x;
            y_vector = target->get_character()->getPosition().y - x[i]->get_enemie()->getPosition().y;
            lenght_vector = sqrt(x_vector * x_vector + y_vector * y_vector);
            normalized_x = (x_vector / lenght_vector);
            normalized_y = (y_vector / lenght_vector);
            x[i]->get_enemie()->move(normalized_x * speed_enemie * time->asSeconds(), normalized_y * speed_enemie * time->asSeconds());
            clock->restart();
        }
    }
}

