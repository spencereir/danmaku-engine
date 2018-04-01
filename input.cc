#include "input.h"

std::vector<Command*> InputHandler::handleInput() {
    std::vector<Command*> ret;
    for (auto p : keymap) {
        bool good = true;
        for (int i = 0; good && i < (int)p.first.size(); i++) {
            good &= sf::Keyboard::isKeyPressed(p.first[i]);
        }
        if (good) ret.push_back(p.second);
    }
    return ret;
}
