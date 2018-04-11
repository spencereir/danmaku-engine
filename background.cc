#include "background.h"
#include "data.h"
#include "resources.h"

Background::Background(std::string filename, Options &options) : t{getResource<sf::Texture>(filename)}, s{t}, options{options} {
}

void Background::draw(sf::RenderWindow &w) {
    w.draw(s);
}
