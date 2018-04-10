#ifndef __DRAWABLE_H_
#define __DRAWABLE_H_

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "entity.h"

// A Drawable is an Entity that can be drawn to a window
// Such drawing is done with a provided spritesheet by default
class Drawable : public virtual Entity {
    int frame;
    int state;
    int rate;
    std::vector< std::vector< sf::Sprite > > spritesheet;

public:
    Drawable() = default;
    Drawable(std::vector< std::vector< std::string > >, int=10);
    void setState(int);
    void setRate(int);
    void draw(sf::RenderWindow&);
};

#endif
