#ifndef __DRAWABLE_H_
#define __DRAWABLE_H_

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "data.h"

class Drawable {
    int frame;
    int state;
    int rate;
    std::vector< std::vector< sf::Sprite > > spritesheet;

public:
    Drawable(std::vector< std::vector< std::string > >, int=10);
    void setState(int);
    void setRate(int);
    void draw(sf::RenderWindow*);
    virtual Vec2 getLocation() = 0;
};

#endif
