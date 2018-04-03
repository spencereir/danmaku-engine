#include "pause.h"
#include "world.h"
#include "resources.h"
#include <SFML/Graphics.hpp>

#define min(a,b) (a < b ? a : b)
#define max(a,b) (a < b ? b : a)

Pause::Pause(Game &g) : Menu{g} {
    old_screen.setColor(sf::Color(255,255,255,128));
    menu_option.push_back("Resume");
    menu_option.push_back("Retry");
    menu_option.push_back("Main Menu");
    menu_option.push_back("Quit");
}

void Pause::select() {
    switch (cursor) {
        case 0:
            parent.popState();
            break;
        case 1:
            parent.popState(2);
            parent.pushState(GameStateType::World);
            break;
        case 2:
            parent.popState(1);
            break;
        case 3:
            parent.popState(0);
            break;
    }
}

void Pause::draw() {
    window.clear();
    window.draw(old_screen);
    sf::Font f = getResource<sf::Font>("resources/fonts/DejaVuSans.ttf");
    int i = 0;
    for (std::string option : menu_option) {
        sf::Text t;
        t.setFont(f);
        t.setString(option);
        t.setCharacterSize(24);
        t.setPosition({400, 200 + 30.f * i});
        if (cursor == i) {
            t.setStyle(sf::Text::Bold);
        }
        window.draw(t);
        i++;
    }
    window.display();
}
