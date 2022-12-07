#include "Character.h"
Character::Character()
{
	life = LIFE;
	damage = DAMAGE;
	sprite = new sf::Sprite;
	texture = new sf::Texture;
    pj_events = new sf::Event();
    move_speed = 2.f;
    reduce_speed = move_speed * 0.5f;
    divide_sprite_x = 3;
    divide_sprite_y = 4;
	if (!texture->loadFromFile("../assets/Character.png"))
	{
		cout << "fail" << endl;
	}
	sprite->setTexture(*texture);
    set_frame(sprite, { 0,0 });
    sprite->setScale(500.f / texture->getSize().x, 500.f / texture->getSize().y);
	sprite->setOrigin(texture->getSize().x * 0.5f, texture->getSize().y * 0.5f);
	sprite->setPosition(1000, 450);
    if (!buffer_reduce_speed.loadFromFile("../assets/punch.wav")) {
        cout << "sound damage error" << endl;
    }
    sound_reduce_speed.setBuffer(buffer_reduce_speed);
    sound_reduce_speed.setVolume(100.f);
}
Character::~Character()
{
	cout << "~Character()" << endl;
	delete sprite;
	delete texture;
    delete pj_events;
}
sf::Sprite* Character::get_character() const
{
	return sprite;
}
int Character::get_life() const
{
	return life;
}
float Character::get_damage() const
{
	return damage;
}
void Character::set_life(int life)
{
	this->life = life;
}
void Character::set_damage(float damage)
{
	this->damage = damage;
}
sf::Sound Character::get_sound() const
{
    return sound_reduce_speed;
}
void Character::recibe_damage(float damage)
{
	life -= damage;
}
void Character::inputs(sf::RenderWindow* ref_window, std::vector<sf::Clock*>clock, std::vector<sf::Time*>time)
{
    //inputs keyboard;
    if (pj_events->KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sprite->move(sf::Vector2f(move_speed, 0.0f));
            set_frame(sprite, { 0,1 });
            if (time[0]->asSeconds() > 1.f) {
                set_frame(sprite, { 1,1 });
            }
            if (time[0]->asSeconds() > 2.f) {
                set_frame(sprite, { 2,1 });
            }
            if (time[0]->asSeconds() > 3.f) {
                set_frame(sprite, { 0,1 });
            }
        }
    }
    if (pj_events->KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sprite->move(sf::Vector2f((-move_speed), 0.0f));
            set_frame(sprite, { 0,3 });
            if (time[1]->asSeconds() > 1) {
              set_frame(sprite, { 1,3 });
            }
            if (time[1]->asSeconds() > 2) {
              set_frame(sprite, { 2,3 });
            }
             if (time[1]->asSeconds() > 3) {
              set_frame(sprite, { 0,3 });
            }
        }
    }
    if (pj_events->KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            sprite->move(sf::Vector2f(0.f, -move_speed));
            set_frame(sprite, { 0,0 });
            if (time[2]->asSeconds() > 1) {
                set_frame(sprite, { 1,0 });
            }
            if (time[2]->asSeconds() > 2) {
                set_frame(sprite, { 2,0 });
            }
            if (time[2]->asSeconds() > 3) {
                set_frame(sprite, { 0,0 });
            }
        }
    }
    if (pj_events->KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sprite->move(sf::Vector2f(0.f, move_speed));
            set_frame(sprite, { 0,2 });
            if (time[3]->asSeconds() > 1) {
                set_frame(sprite, { 1,2 });
            }
            if (time[3]->asSeconds() > 2) {
                set_frame(sprite, { 2,2 });
            }
            if (time[3]->asSeconds() > 3) {
                set_frame(sprite, { 0,2 });
            }
        }
    }
    if (pj_events->KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            ref_window->close();
        }
    }
    //restart clocks
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        clock[0]->restart();
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        clock[1]->restart();
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        clock[2]->restart();
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        clock[3]->restart();
    }
}
void Character::collisions(Landscape* landscape_ref)
{
    //Earth
    if (sprite->getGlobalBounds().intersects(landscape_ref->get_sky()->getGlobalBounds())) {
        sprite->setColor(sf::Color::Color(200, 200, 200, 255));
        move_speed = 2.0f;
    }
    //rivers
    if (sprite->getGlobalBounds().intersects(landscape_ref->get_river()->getGlobalBounds())) {
        sprite->setColor(sf::Color::Blue);
        move_speed = reduce_speed;
        sound_reduce_speed.play();
    }
    else if (sprite->getGlobalBounds().intersects(landscape_ref->get_river_2()->getGlobalBounds())) {
        sprite->setColor(sf::Color::Blue);
        move_speed = reduce_speed;
        sound_reduce_speed.play();
    }
    else if (sprite->getGlobalBounds().intersects(landscape_ref->get_river_3()->getGlobalBounds())) {
        sprite->setColor(sf::Color::Blue);
        move_speed = reduce_speed;
        sound_reduce_speed.play();
    }
    else if (sprite->getGlobalBounds().intersects(landscape_ref->get_river_4()->getGlobalBounds())) {
        sprite->setColor(sf::Color::Blue);
        move_speed = reduce_speed;
        sound_reduce_speed.play();
    }
    else if (sprite->getGlobalBounds().intersects(landscape_ref->get_river_5()->getGlobalBounds())) {
        sprite->setColor(sf::Color::Blue);
        move_speed = reduce_speed;
        sound_reduce_speed.play();
    }
    //box
    if (sprite->getGlobalBounds().intersects(landscape_ref->get_box()->getGlobalBounds())) {
        sprite->setColor(sf::Color::Blue);
        move_speed = reduce_speed;
        sound_reduce_speed.play();
    }
    //screen
    if (sprite->getPosition().x <140.f) {
        sprite->setPosition(140.f, sprite->getPosition().y);
    }
    else if (sprite->getPosition().x >= WIDTH_SCREEN + 200) {
        sprite->setPosition(WIDTH_SCREEN + 200, sprite->getPosition().y);
    }
    else if (sprite->getPosition().y < 190.f) {
        sprite->setPosition(sprite->getPosition().x, 190.f);
    }
    else if (sprite->getPosition().y >= HEIGHT_SCREEN + 200) {
        sprite->setPosition(sprite->getPosition().x, HEIGHT_SCREEN + 200);
    }
}
void Character::set_frame(sf::Sprite* ref, sf::Vector2i number_frames)
{
    sf::IntRect poisicon(number_frames.x * (ref->getTexture()->getSize().x / divide_sprite_x), number_frames.y * (ref->getTexture()->getSize().y / divide_sprite_y), ref->getTexture()->getSize().x / divide_sprite_x, ref->getTexture()->getSize().y / divide_sprite_y);
    ref->setTextureRect(poisicon);
}