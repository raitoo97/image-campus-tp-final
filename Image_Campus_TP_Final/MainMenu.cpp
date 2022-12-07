#include "MainMenu.h"
MainMenu::MainMenu()
{
    window_menu = new sf::RenderWindow(sf::VideoMode(WIDTH_SCREEN_MENU, HEIGHT_SCREEN_MENU), TITLE_TITLE);
    window_menu->setMouseCursorVisible(false);
    window_menu->setFramerateLimit(60);
    event_menu = new sf::Event();
    music_menu = new sf::Music();
}
MainMenu::~MainMenu()
{
    cout << "~MainMenu()" << endl;
}
bool MainMenu::init_menu()
{
    //wallpaper
    if (!t_menu.loadFromFile("../assets/Wallpaper .jpg"))
    {
        cout << "fail" << endl;
        return false;
    }
    s_menu.setTexture(t_menu);
    s_menu.setScale(WIDTH_SCREEN_MENU / t_menu.getSize().x, HEIGHT_SCREEN_MENU / t_menu.getSize().y);
    //BOTTONS
    if (!font_menu.loadFromFile("../assets/Vecna Bold Italic.otf"))
    {
        cout << "the font cannot load" << endl;
        return false;
    }
    //fonts
    texts_menu[0].setFont(font_menu);
    texts_menu[1].setFont(font_menu);
    texts_menu[2].setFont(font_menu);
    //string
    texts_menu[0].setString("New Game");
    texts_menu[1].setString("Options");
    texts_menu[2].setString("Exit");
    //color
    texts_menu[0].setFillColor(sf::Color::Black);
    texts_menu[1].setFillColor(sf::Color::Black);
    texts_menu[2].setFillColor(sf::Color::Black);
    //size
    texts_menu[0].setCharacterSize(70);
    texts_menu[1].setCharacterSize(70);
    texts_menu[2].setCharacterSize(70);
    //position
    texts_menu[0].setPosition(WIDTH_SCREEN_MENU * 0.5f - 200, HEIGHT_SCREEN_MENU * 0.5f - 300);
    texts_menu[1].setPosition(WIDTH_SCREEN_MENU * 0.5f - 200, HEIGHT_SCREEN_MENU * 0.5f - 150);
    texts_menu[2].setPosition(WIDTH_SCREEN_MENU * 0.5f - 200, HEIGHT_SCREEN_MENU * 0.5f);
    //gun_sight
    if (!t_menu_gun_sight.loadFromFile("../assets/gun_sight.png"))
    {
        cout << "fail" << endl;
        return false;
    }
    s_menu_gun_sight.setTexture(t_menu_gun_sight);
    //Music
    if (!music_menu->openFromFile("../assets/menu_music.wav"))
    {
        cout << "fail" << endl;
        return false;
    }
    music_menu->play();
    music_menu->setVolume(100);
    music_menu->setLoop(true);
    //mouse
    if (!mouse_menu_t.loadFromFile("../assets/mouse_cick.jpg"))
    {
        cout << "fail" << endl;
        return false;
    }
    mouse_menu_s.setTexture(mouse_menu_t);
    mouse_menu_s.setPosition(1650, 0);
    mouse_menu_s.setScale(200.f / mouse_menu_t.getSize().x, 200.f / mouse_menu_t.getSize().y);
    //wasd
    if (!wasd_menu_t.loadFromFile("../assets/wasd.png"))
    {
        cout << "fail" << endl;
        return false;
    }
    wasd_menu_s.setTexture(wasd_menu_t);
    wasd_menu_s.setPosition({ 20,20 });
    wasd_menu_s.setScale(250.f / wasd_menu_t.getSize().x, 250.f / wasd_menu_t.getSize().y);
    //tutorial
    if (!font_tutorial.loadFromFile("../assets/Kingthings Petrock.ttf"))
    {
        cout << "the font cannot load" << endl;
        return false;
    }
    text_wasd_mouse[0].setFont(font_tutorial);
    text_wasd_mouse[1].setFont(font_tutorial);
    text_wasd_mouse[0].setFillColor(sf::Color::Black);
    text_wasd_mouse[1].setFillColor(sf::Color::Black);
    text_wasd_mouse[0].setString("Move");
    text_wasd_mouse[1].setString(string("Shot Fireball"));
    text_wasd_mouse[0].setCharacterSize(50);
    text_wasd_mouse[1].setCharacterSize(50);
    text_wasd_mouse[0].setPosition(80,270);
    text_wasd_mouse[1].setPosition(1650,160);
	return true;
}
void MainMenu::loop_menu()
{
    while (window_menu->isOpen())
    {
        while (window_menu->pollEvent(*event_menu))
        {
            if (event_menu->type == sf::Event::Closed) {
                window_menu->close();
            }
        }
        //functions
        input_menu();
        collision_menu();
        window_menu->clear();
        drawing_menu();
        window_menu->display();
    }
}
void MainMenu::stop_menu()
{
    delete window_menu;
    delete event_menu;
    delete music_menu;
    cout << "~MainMenu()_stop" << endl;
}
void MainMenu::input_menu()
{
    if (event_menu->KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            exit(1);
        }
    }
    if (event_menu->MouseMoved) {
        mouse_pos_menu = sf::Mouse::getPosition(*window_menu);
        s_menu_gun_sight.setPosition(mouse_pos_menu.x + MOUSEX_MARGEN_MENU, mouse_pos_menu.y + MOUSEY_MARGEN_MENU);
    }
    if (event_menu->KeyPressed) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (s_menu_gun_sight.getGlobalBounds().intersects(texts_menu[0].getGlobalBounds())){
                window_menu->close();
            }
            else if (s_menu_gun_sight.getGlobalBounds().intersects(texts_menu[2].getGlobalBounds())) {
                exit(1);
            }
        }
    }
}
void MainMenu::drawing_menu()
{
    window_menu->draw(s_menu);
    for (auto texts_menu_for : texts_menu) {
        window_menu->draw(texts_menu_for);
    }
    window_menu->draw(mouse_menu_s);
    window_menu->draw(wasd_menu_s);
    for (auto tutorial_text : text_wasd_mouse) {
        window_menu->draw(tutorial_text);
    }
    window_menu->draw(s_menu_gun_sight);
}
void MainMenu::collision_menu()
{
    for (int i = 0; i < MAX_SIZE_BOTTONS; i++) {
        if (s_menu_gun_sight.getGlobalBounds().intersects(texts_menu[i].getGlobalBounds())) {
            texts_menu[i].setFillColor(sf::Color::Red);
        }
        else {
            texts_menu[i].setFillColor(sf::Color::Black);
        }
    }
}
