#include "menu.h"
#include "resources.h"

#define min(a,b) (a < b ? a : b)
#define max(a,b) (a < b ? b : a)

void Menu::handleInput(sf::Event event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    cursor = max(cursor-1, 0);
                    break;
                case sf::Keyboard::Down:
                    cursor = min(cursor+1, (int)menu_option.size()-1);
                    break;
            }
            break;
    }
}

void Menu::update() {}

void Menu::draw() {
    window->clear();
    sf::Font f = getResource<sf::Font>("resources/fonts/DejaVuSans.ttf");
    int i = 0;
    for (std::string option : menu_option) {
        sf::Text t(option, f);
        t.setCharacterSize(24);
        t.setPosition({400, 200 + 32.f * i});
        if (cursor == i) {
            t.setFillColor(sf::Color::Green);
        }
        window->draw(t);
        i++;
    }
    window->display();
}
