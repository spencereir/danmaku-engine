#include "main_menu.h"
#include "resources.h"
#include "world.h"
#include "main_options_menu.h"

MainMenu::MainMenu(Game &g) : Menu{g} {
    menu_option = {"Start Game", "Options", "Quit"};
}

void MainMenu::select() {
    switch (cursor) {
        case 0:
            parent.pushState(GameStateType::World);
            break;
        case 1:
            parent.pushState(GameStateType::MainOptionsMenu);
            break;
        case 2:
            parent.popState();
            break;
    }
}
