#include "options_menu.h"
#include "resources.h"
#include "input.h"

#define clip(x,a,b) (x < a ? a : (x > b ? b : x))
#define max(a,b) (a < b ? b : a)

OptionsMenu::OptionsMenu(Game *g) : GameState{g} {
    setKeymap({
        { {}, {sf::Keyboard::Left}, new Commands::OptionsMenu::CursorLeft{this}},
        { {}, {sf::Keyboard::Right}, new Commands::OptionsMenu::CursorRight{this}},
        { {}, {sf::Keyboard::Down}, new Commands::OptionsMenu::CursorDown{this}},
        { {}, {sf::Keyboard::Up}, new Commands::OptionsMenu::CursorUp{this}},
        { {}, {sf::Keyboard::Return}, new Commands::OptionsMenu::Select{this}}
    });
}

void OptionsMenu::moveCursor(int dx, int dy) {
    cursor = clip(cursor+dx, 0, (int)max(subcursor.size(), menu_option.size())-1);
    subcursor[cursor] = clip(subcursor[cursor]+dy, 0, (int)submenu_option[cursor].size()-1);
}

void OptionsMenu::update() {}

void OptionsMenu::draw() {
    int start_x  = 100;
    int start_y  = 100;
    int padding  = 5;
    int deadzone = 50;
    int charsize = 24;
    int sm_charsize = 20;
    int max_x = 0;
    sf::Font f = getResource<sf::Font>("resources/fonts/DejaVuSans.ttf");

    for (int i = 0; i < (int)menu_option.size(); i++) {
        sf::Text t(menu_option[i], f, charsize);
        t.setPosition({(float)start_x, (float)start_y + (charsize + padding) * i});
        if (cursor == i) t.setFillColor(sf::Color::Green);
        max_x = max(max_x, start_x + (int)t.getLocalBounds().width);
        window->draw(t);
    }

    for (int j = 0;; j++) {
        int next_max_x = max_x;
        bool drew_one = false;
        for (int i = 0; i < (int)submenu_option.size(); i++) {
            if (j >= (int)submenu_option[i].size()) continue;
            drew_one = true;
            sf::Text t(submenu_option[i][j], f, sm_charsize);
            t.setPosition({(float)max_x + deadzone, (float)start_y + (charsize + padding) * i});
            if (subcursor[i] == j) {
                if (i < (int)menu_option.size()) {
                     t.setFillColor(sf::Color::Red);
                } else if (cursor == i) {
                    t.setFillColor(sf::Color::Green);
                }
            }
            next_max_x = max(next_max_x, max_x + deadzone + (int)t.getLocalBounds().width);
            window->draw(t);
        }
        if (!drew_one) break;
        max_x = next_max_x;
    }
}
