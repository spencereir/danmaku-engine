#include "drawable.h"
#include "resources.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

Drawable::Drawable(std::vector< std::vector< std::string > > resource_locations, int rate) : frame{0}, state{0}, rate{rate} {
    spritesheet.resize(resource_locations.size());
    int i = 0;
    for (auto &rv : resource_locations) {
        spritesheet[i].resize(rv.size());
        int j = 0;
        for (auto &r : rv) {
            spritesheet[i][j] = sf::Sprite{getResource<sf::Texture>(r)};
            j++;
        }
        i++;
    }
}

void Drawable::setState(int _state) {
    state = _state;
    frame = 0;
}

void Drawable::setRate(int _rate) {
    rate = _rate;
}

void Drawable::draw(sf::RenderWindow &w) {
    sf::Sprite &s = spritesheet[state][frame/rate];
    Vec2 loc = getLocation();
    s.setPosition({(float)loc.x-s.getLocalBounds().width/2, (float)loc.y-s.getLocalBounds().height/2});
    w.draw(s);
    frame++;
    if (frame >= rate*(int)spritesheet[state].size()) frame = 0;
}
