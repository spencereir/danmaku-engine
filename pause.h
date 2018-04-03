#ifndef __PAUSE_H_
#define __PAUSE_H_

#include <SFML/Graphics.hpp>
#include "menu.h"

class Pause : public Menu {
    sf::Texture tex;
    sf::Sprite old_screen;

public:
    Pause(Game&);
    void select();
    void draw() override;
};

#endif
