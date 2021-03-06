#include <set>
#include "input.h"
#include "menu.h"
#include "options_menu.h"
#include "world.h"
#include "player.h"
#include "game.h"

std::vector< std::shared_ptr< Command > > InputHandler::handleInput(sf::RenderWindow &window) {
    std::set< sf::Keyboard::Key > key_pressed;
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            g.close();
            return {};
        } else if (event.type == sf::Event::KeyPressed) {
            key_pressed.insert(event.key.code);
        }
    }

    std::vector< std::shared_ptr< Command > > ret;
    for (auto p : keymap) {
        bool good = true;
        for (int i = 0; good && i < (int)std::get<0>(p).size(); i++) {
            good &= sf::Keyboard::isKeyPressed(std::get<0>(p)[i]);
        }
        for (int i = 0; good && i < (int)std::get<1>(p).size(); i++) {
            good &= (key_pressed.find(std::get<1>(p)[i]) != key_pressed.end());
        }
        if (good) ret.push_back(std::get<2>(p));
    }
    return ret;
}

void Command::execute() {
}

void Commands::Menu::CursorDown::execute() {
    menu.moveCursor(1);
}

void Commands::Menu::CursorUp::execute() {
    menu.moveCursor(-1);
}
void Commands::Menu::Select::execute() {
    menu.select();
}

void Commands::OptionsMenu::CursorDown::execute() {
    menu.moveCursor(1, 0);
}

void Commands::OptionsMenu::CursorUp::execute() {
    menu.moveCursor(-1, 0);
}

void Commands::OptionsMenu::CursorLeft::execute() {
    menu.moveCursor(0, -1);
}

void Commands::OptionsMenu::CursorRight::execute() {
    menu.moveCursor(0, 1);
}

void Commands::OptionsMenu::Select::execute() {
    menu.select();
}

void Commands::Player::MoveLeft::execute() {
    player.getVelocity().x -= vel;
}

void Commands::Player::MoveRight::execute() {
    player.getVelocity().x += vel;
}

void Commands::Player::MoveUp::execute() {
    player.getVelocity().y -= vel;
}

void Commands::Player::MoveDown::execute() {
    player.getVelocity().y += vel;
}

void Commands::Player::Shoot::execute() {
    for (auto x : player.getBullets()) {
        world.registerPlayerBullet(x);
    }
}

void Commands::Player::Bomb::execute() {

}

void Commands::World::Pause::execute() {
    world.getParent().getClock().pause();
    world.getParent().pushState(GameStateType::PauseMenu);
}
