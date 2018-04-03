#include "main_options_menu.h"

MainOptionsMenu::MainOptionsMenu(Game &g) : OptionsMenu{g} {
    cursor = 0;
    menu_option = {"Some setting 1", "Some setting 2", "Are you happy alex"};
    subcursor = {0, 0, 0, 0};
    submenu_option = {{"Setting 1-1", "Setting 1-2"}, {"Setting 2-1", "Setting 2-2", "Setting 2-3"}, {"Setting 3-1", "Setting 3-2"}, {"Save", "Default"}};
}

void MainOptionsMenu::select() {
    parent.popState();
}

void MainOptionsMenu::draw() {
    window.clear();
    OptionsMenu::draw();
    window.display();
}
