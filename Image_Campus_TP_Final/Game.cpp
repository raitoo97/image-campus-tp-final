#include "Game.h"
Game::Game()
{
    //condition to lose
    game_over = false;
    //class window
    window = new sf::RenderWindow(sf::VideoMode(WIDTH_SCREEN, HEIGHT_SCREEN), TITLE);
    window->setFramerateLimit(60);
    window->setMouseCursorVisible(false);
    landscape = new Landscape();
    //classes
    dragon = new Character();
    event = new sf::Event();
    //enemies
    enemie.push_back(new Enemie(ENEMY_LIFE,ENEMY_DAMAGE, 600, 450));
    enemie.push_back(new Enemie(ENEMY_LIFE, ENEMY_DAMAGE, 300, 200));
    enemie.push_back(new Enemie(ENEMY_LIFE, ENEMY_DAMAGE));
    //times
    clock_action = new sf::Clock();
    time_action = new sf::Time();
    clock_spawn = new sf::Clock();
    time_spawn = new sf::Time();
    clock_change_color = new sf::Clock();
    time_change_color = new sf::Time();
    clock_scape = new sf::Clock();
    time_scape = new sf::Time();
    clock_sound_explosion = new sf::Clock();
    time_sound_explosion = new sf::Time();
    //Clocks move and times move
    clocks_move_pj.push_back(new sf::Clock());
    clocks_move_pj.push_back(new sf::Clock());
    clocks_move_pj.push_back(new sf::Clock());
    clocks_move_pj.push_back(new sf::Clock());
    times_move_pj.push_back(new sf::Time());
    times_move_pj.push_back(new sf::Time());
    times_move_pj.push_back(new sf::Time());
    times_move_pj.push_back(new sf::Time());
    //score
    kills = 0;
    //mouse
    mouse_pos = { 0,0 };
    //spawn
    rand_num = 0;
    poision_x = 0.f;
    posicion_Y = 0.f;
    //textures and sprites
    t_gun_sight = new sf::Texture();
    s_gun_sight = new sf::Sprite();
    t_explosion = new sf::Texture();
    s_explosion = new sf::Sprite();
    //explosion frames
    current_frame.x = 0;
    current_frame.y = 0;
    show_eplosion = false;
    //final screen
    layer_final = new sf::RectangleShape({ WIDTH_SCREEN,HEIGHT_SCREEN });
}
Game::~Game()
{
    delete window;
    cout << "~Window()" << endl;
}
bool Game::init()
{
    //text
    if (!font_life.loadFromFile("../assets/life_text.ttf"))
    {
        cout << "the font cannot load" << endl;
        return false;
    }
    //Music_sounds
    if (!music.openFromFile("../assets/Ambient_music.ogg")) {
        cout << "music ambient error" << endl;
        return false;
    }
    if (!music_zombie.openFromFile("../assets/Zombie-sound-effect.wav")) {
        cout << "music zombie error" << endl;
        return false;
    }
    if (!sound_explosion.openFromFile("../assets/Explosion.wav")) {
        cout << "music explosion error" << endl;
        return false;
    }
    //sprites
    if (!t_gun_sight->loadFromFile("../assets/gun_sight.png"))
    {
        cout << "gun_sight error" << endl;
        return false;
    }
    if (!t_explosion->loadFromFile("../assets/Explosion.png"))
    {
        cout << "explosion error" << endl;
        return false;
    }
    //text life config
    text_life.setFont(font_life);
    text_life.setCharacterSize(50);
    text_life.setFillColor(sf::Color::Red);
    text_life.setPosition(0.f, 0.f);
    text_life.setOutlineColor(sf::Color::Black);
    text_life.setOutlineThickness(3.f);
    //text score
    text_score.setFont(font_life);
    text_score.setCharacterSize(50);
    text_score.setFillColor(sf::Color::Red);
    text_score.setPosition(1700.f, 0.f);
    text_score.setOutlineColor(sf::Color::Black);
    text_score.setOutlineThickness(3.f);
    //final test
    text_escape.setFont(font_life);
    text_escape.setCharacterSize(50);
    text_escape.setPosition((WIDTH_SCREEN * 0.5f) + 230 - 650.f, 200);
    text_escape.setOutlineColor(sf::Color::Black);
    text_escape.setOutlineThickness(3.f);
    text_escape.setString(string("thanks for playing! ... Press scape to exit!"));;
    //Zombie_song
    music_zombie.setVolume(10.f);
    music_zombie.play();
    music_zombie.setLoop(true);
    //music_ambient
    music.setVolume(100.f);
    music.play();
    music.setLoop(true); 
    //sprites gunsight
    s_gun_sight->setTexture(*t_gun_sight);
    //sprites explosion
    s_explosion->setTexture(*t_explosion);
    explosions_frame(s_explosion,{current_frame.x,current_frame.y});
    //final screen
    layer_final->setFillColor(sf::Color::Black);
    return true;
}
void Game::loop()
{
    while (window->isOpen())
    {
        while (window->pollEvent(*event))
        {
            if (event->type == sf::Event::Closed) {
                window->close();
            }if (dragon->get_life() <= 0) {
                game_over = true;//ver en drawing() secuencia final
            }
        }
        //Init times move
        *times_move_pj[0] = clocks_move_pj[0]->getElapsedTime();
        *times_move_pj[1] = clocks_move_pj[1]->getElapsedTime();
        *times_move_pj[2] = clocks_move_pj[2]->getElapsedTime();
        *times_move_pj[3] = clocks_move_pj[3]->getElapsedTime();
        //texts
        text_life.setString(string("Life: " + to_string(dragon->get_life())));
        text_score.setString(string("Kills: " + to_string(kills)));
        //time
        *time_sound_explosion = clock_sound_explosion->getElapsedTime();
        *time_action = clock_action->getElapsedTime();
        *time_spawn = clock_spawn->getElapsedTime();
        *time_change_color = clock_change_color->getElapsedTime();
        *time_scape = clock_scape->getElapsedTime();
        //functions pj
        dragon_atack();
        dragon->inputs(window, clocks_move_pj, times_move_pj);
        dragon->collisions(landscape);
        //functions_enemie
        spawn_enemies();
        for (int i = 0; i < enemie.size(); i++) {
            enemie[i]->ia_controller(dragon, enemie, clock_action, time_action, ENEMY_DAMAGE);
            enemie[i]->enemy_change_color(enemie, clock_change_color, time_change_color, landscape);
        }
        //drawing
        window->clear();
        drawing();
        window->display();
    }
}
void Game::stop()
{
    //delete enmies
    for (auto enemy : enemie) {
        delete enemy;
    }
    enemie.clear();
    cout << "enemies size:" << enemie.size() << endl;
    //delete clocks move
    for (auto clock_move : clocks_move_pj) {
        delete clock_move;
    }
    clocks_move_pj.clear();
    cout << "cloks move size:" << clocks_move_pj.size() << endl;
    //delete times moves
    for (auto time_move : times_move_pj) {
        delete time_move;
    }
    times_move_pj.clear();
    cout << "time move size:" << times_move_pj.size() << endl;
    //
    delete dragon;
    delete event;
    delete clock_action;
    delete time_action;
    delete clock_spawn;
    delete time_spawn;
    delete clock_change_color;
    delete time_change_color;
    delete layer_final;
    delete clock_scape;
    delete time_scape;
    delete t_gun_sight;
    delete s_gun_sight;
    delete t_explosion;
    delete s_explosion;
    delete clock_sound_explosion;
    delete time_sound_explosion;
    delete landscape;
    cout << "~Window()_stop" << endl;
}
void Game::dragon_atack()
{
    //mouse
    if (event->MouseMoved) {
        mouse_pos = sf::Mouse::getPosition(*window);
        s_gun_sight->setPosition((float)mouse_pos.x + MOUSEX_MARGEN, (float)mouse_pos.y + MOUSEY_MARGEN);
    }
    if (event->KeyPressed) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            show_eplosion = true;
            //sound
            if (time_sound_explosion->asSeconds() > 1.f) {
                sound_explosion.setVolume(40);
                sound_explosion.play();
                clock_sound_explosion->restart();
            }
            //move sprite explosion
            if (current_frame.x < 4) {
                current_frame.x++;
            }
            else {
                current_frame.x = 0;
            }
            s_explosion->setPosition(s_gun_sight->getPosition().x-50.f, s_gun_sight->getPosition().y-50.f);
            explosions_frame(s_explosion, current_frame);
            //atack
            for (int i = 0; i < enemie.size(); i++) {
                if (s_gun_sight->getGlobalBounds().intersects(enemie[i]->get_enemie()->getGlobalBounds())) {
                    enemie[i]->get_enemie()->setColor(sf::Color::Red);
                    enemie[i]->recibe_damage(dragon->get_damage());
                    if (enemie[i]->get_life() <= 0) {
                        enemie.erase(enemie.begin() + i);
                        kills++;
                        break;
                    }
                    break;
                }
            }
        }
    }
    if (event->KeyReleased) {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            show_eplosion = false;
        }
    }
}
void Game::drawing()
{
    //draw landscape
    window->draw(*landscape->get_sky());
    window->draw(*landscape->get_box());
    window->draw(*landscape->get_river());
    window->draw(*landscape->get_river_2());
    window->draw(*landscape->get_river_3());
    window->draw(*landscape->get_river_4());
    window->draw(*landscape->get_river_5());
    window->draw(*landscape->get_layer());
    //texts
    window->draw(text_life);
    window->draw(text_score);
    //sprites
    window->draw(*s_gun_sight);
    //draw enemies
    for (int i = 0; i < enemie.size(); i++) {
        window->draw(*enemie[i]->get_enemie());
    }
    //draw character
    window->draw(*dragon->get_character());
    //explosion
    if (show_eplosion) {
        window->draw(*s_explosion);
    }
    //final screen
    if (game_over) {
        window->draw(*layer_final);
        window->draw(text_score);
        window->draw(text_escape);
        text_escape.setFillColor(sf::Color::Red);
        if (time_scape->asSeconds() > 1.25f) {
            text_escape.setFillColor(sf::Color::Black);
            if (time_scape->asSeconds() > 1.5f) {
                clock_scape->restart();
            }
        }
        text_score.setPosition((WIDTH_SCREEN * 0.5f)-650.f, (HEIGHT_SCREEN * 0.5f) - 300.f);
        text_score.setCharacterSize(500);
        dragon->get_sound().setVolume(0);
        sound_explosion.setVolume(0);
        music_zombie.setVolume(0);
    }   
}
void Game::spawn_enemies()
{
    srand(time(NULL));
    if (time_spawn->asSeconds() > TIME_TO_SPAWN) {
        rand_num = rand() % 10 + 1;
        poision_x = rand() % WIDTH_SCREEN + 1;
        posicion_Y = rand() % HEIGHT_SCREEN + 1;
        if (rand_num > 3) {
            enemie.push_back(new Enemie(ENEMY_LIFE, ENEMY_DAMAGE, poision_x, posicion_Y));
            clock_spawn->restart();
        }else {
            clock_spawn->restart();
        }
    }
}
void Game::explosions_frame(sf::Sprite* ref, sf::Vector2i number_frames)
{
    sf::IntRect poisicon(number_frames.x * (ref->getTexture()->getSize().x / 5), number_frames.y * ref->getTexture()->getSize().y,(ref->getTexture()->getSize().x / 5), ref->getTexture()->getSize().y);
    ref->setTextureRect(poisicon);
}

