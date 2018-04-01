#include "main_menu.h"
#include "resources.h"
#include "world.h"
#include "main_options_menu.h"

MainMenu::MainMenu(Game *g) : Menu{g} {
    menu_option.push_back("Start Game");
    menu_option.push_back("Options");
    menu_option.push_back("Quit");
}

void MainMenu::select() {
    switch (cursor) {
        case 0:
            parent->pushState(new World{parent});
            break;
        case 1:
            parent->pushState(new MainOptionsMenu{parent});
            break;
        case 2:
            parent->popState();
            break;
    }
}
