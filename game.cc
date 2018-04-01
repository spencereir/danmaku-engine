#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "data.h"
#include "world.h"
#include "main_menu.h"
#include "input.h"

Game::Game(std::string options_file) : options{loadOptionsFromFile(options_file)}, window{new sf::RenderWindow{sf::VideoMode(options.SCREEN_WIDTH, options.SCREEN_HEIGHT), options.WINDOW_TITLE}}, finished{false}, state{new MainMenu{this}} {
    window->setFramerateLimit(options.FRAME_LIMIT);
}

Game::~Game() {
    window->close();
}

void Game::handleInput() {
    if (state.empty()) finished = true;
    else state.back()->handleInput();
}
    /*
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close(), finished = true;
        else if (!state.empty())
            state.back()->handleInput(event);
    }
}*/

void Game::update() {
    if (state.empty()) finished = true;
    else state.back()->update();
}

void Game::draw() {
    if (state.empty()) finished = true;
    else state.back()->draw();
}

void Game::popState(int to_size) {
    if (to_size < 0) {
        delete state.back();
        state.pop_back();
        return;
    }
    while ((int)state.size() > to_size) {
        delete state.back();
        state.pop_back();
    }
}

GameState::GameState(Game *g, std::vector< std::pair< std::vector< sf::Keyboard::Key >, Command* > > keymap) : parent{g}, window{g->getWindow()}, ih{new InputHandler{keymap}} {}

void GameState::handleInput() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            parent->popState(0);
    }

    std::vector<Command*> input = ih->handleInput();
    for (Command *c : input) {
        c->execute(this);
    }
}
