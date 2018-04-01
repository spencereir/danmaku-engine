#ifndef __MENU_H_
#define __MENU_H_

#include <vector>
#include "game.h"

class Menu : public GameState {
protected:
    int cursor;
    std::vector<std::string> menu_option;

public:
    Menu(Game *g) : GameState{g}, cursor{0} {}
    virtual ~Menu() = default;

    virtual void handleInput(sf::Event);
    virtual void update();
    virtual void draw();
};

#endif
