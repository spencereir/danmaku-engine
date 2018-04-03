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
    delete window;
    popState(0);
}

void Game::handleInput() {
    if (state.empty()) finished = true;
    else state.back()->handleInput();
}

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

GameState::GameState(Game *g) : parent{g}, window{g->getWindow()}, ih{new InputHandler} {}

GameState::~GameState() {
    delete ih;
}

void GameState::setKeymap(Keymap keymap) {
    ih->setKeymap(keymap);
}

void GameState::handleInput() {
    std::vector<Command*> input = ih->handleInput(window);
    for (Command *c : input) {
        c->execute();
    }
}
