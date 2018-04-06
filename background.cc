#include "background.h"
#include "data.h"
#include "resources.h"

Background::Background(std::string filename, Options &options) : t{getResource<sf::Texture>(filename)}, s{t, {0, 0, options.SCREEN_WIDTH, options.SCREEN_HEIGHT}}, options{options} {
    t.setRepeated(true);
    y = t.getSize().y - options.SCREEN_HEIGHT;
    s.setTextureRect({0, (int)y, options.SCREEN_WIDTH, options.SCREEN_HEIGHT});
}

void Background::move(int frames) {
    y -= frames;
    s.setTextureRect({0, (int)y, options.SCREEN_WIDTH, options.SCREEN_HEIGHT});
}

void Background::draw(sf::RenderWindow &w) {
    w.draw(s);
}
