#ifndef __OPTIONS_MENU_
#define __OPTIONS_MENU_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "game.h"

class OptionsMenu : public GameState {
protected:
    int cursor;
    std::vector< std::string > menu_option;
    std::vector< int > subcursor;
    std::vector< std::vector< std::string > > submenu_option;

public:
    OptionsMenu(Game &g);
    virtual ~OptionsMenu() = default;

    void moveCursor(int dx, int dy);
    virtual void select() = 0;

    virtual void update();
    virtual void draw();
};

#endif
