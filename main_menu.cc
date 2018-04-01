#include "main_menu.h"
#include "resources.h"
#include "world.h"
#include "main_options_menu.h"

MainMenu::MainMenu(Game *g) : Menu{g} {
    menu_option.push_back("Start Game");
    menu_option.push_back("Options");
    menu_option.push_back("Quit");
}

void MainMenu::handleInput(sf::Event event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Return:
                    switch (cursor) {
                        case 0: // Start Game
                            parent->pushState(new World{parent});
                            break;
                        case 1: // Options
                            parent->pushState(new MainOptionsMenu{parent});
                            break;
                        case 2: // Quit
                            parent->popState();
                            break;
                    }
                    break;
                default:
                    Menu::handleInput(event);
            }
            break;
    }
}
