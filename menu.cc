#include "menu.h"
#include "resources.h"

#define clip(x,a,b) (x < a ? a : (x > b ? b : x))

Menu::Menu(Game *g) : GameState{g}, cursor{0} {
    setKeymap({
        { {}, {sf::Keyboard::Up}, new Commands::Menu::CursorUp{this}},
        { {}, {sf::Keyboard::Down}, new Commands::Menu::CursorDown{this}},
        { {}, {sf::Keyboard::Return}, new Commands::Menu::Select{this}}
    });
};
void Menu::moveCursor(int delta) {
    cursor = clip(cursor + delta, 0, (int)menu_option.size()-1);
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
