#ifndef __BACKGROUND_H_
#define __BACKGROUND_H_

#include <SFML/Graphics.hpp>
#include "data.h"

class Background {
    sf::Texture t;
    sf::Sprite s;
    Options &options;
    double y;
public:
    Background(std::string filename, Options &options);
    void move(int frame);
    void draw(sf::RenderWindow &w);
};

#endif
