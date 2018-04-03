#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "data.h"
#include "world.h"
#include "pause.h"
#include "main_options_menu.h"
#include "main_menu.h"
#include "input.h"

Game::Game(std::string options_file) : options{loadOptionsFromFile(options_file)}, window{sf::VideoMode(options.SCREEN_WIDTH, options.SCREEN_HEIGHT), options.WINDOW_TITLE}, finished{false} {
    pushState(GameStateType::MainMenu);
    window.setFramerateLimit(options.FRAME_LIMIT);
}

Game::~Game() {
    window.close();
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

void Game::pushState(GameStateType gst) {
    switch (gst) {
        case GameStateType::MainMenu:
            state.push_back(std::make_shared<MainMenu>(*this));
            break;
        case GameStateType::PauseMenu:
            state.push_back(std::make_shared<Pause>(*this));
            break;
        case GameStateType::MainOptionsMenu:
            state.push_back(std::make_shared<MainOptionsMenu>(*this));
            break;
        case GameStateType::World:
            state.push_back(std::make_shared<World>(*this));
            break;
    }
}

void Game::popState(int to_size) {
    if (to_size < 0) {
        state.pop_back();
        return;
    }
    while ((int)state.size() > to_size) {
        state.pop_back();
    }
}

GameState::GameState(Game &g) : parent{g}, window{g.getWindow()}, ih{std::make_unique<InputHandler>()} {}

void GameState::setKeymap(Keymap keymap) {
    ih->setKeymap(keymap);
}

void GameState::handleInput() {
    std::vector< std::shared_ptr<Command> > input = ih->handleInput(window);
    for (std::shared_ptr<Command> c : input) {
        c->execute();
    }
}
