#ifndef __MAIN_OPTIONS_MENU_
#define __MAIN_OPTIONS_MENU_

#include "options_menu.h"

class Game;

class MainOptionsMenu : public OptionsMenu {
public:
    MainOptionsMenu(Game*);
    void select();
    void draw() override;
};

#endif
