#ifndef __MAIN_MENU_H_
#define __MAIN_MENU_H_

#include <SFML/Graphics.hpp>
#include "menu.h"

class Game;

class MainMenu : public Menu {
public:
    MainMenu(Game*);
    void select();
};

#endif
