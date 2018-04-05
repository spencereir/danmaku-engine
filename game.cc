#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "data.h"
#include "world.h"
#include "pause.h"
#include "main_options_menu.h"
#include "main_menu.h"
#include "input.h"
#include "player.h"

Game::Game(std::string options_file) : options{loadOptionsFromFile(options_file)}, window{sf::VideoMode(options.SCREEN_WIDTH, options.SCREEN_HEIGHT), options.WINDOW_TITLE}, finished{false} {
    pushState(GameStateType::MainMenu);
    window.setFramerateLimit(options.FRAME_LIMIT);
}

Game::~Game() {
    window.close();
    popState(0);
}

#include <iostream>

void Game::handleInput() {
    while (!new_states.empty()) {
        auto p = new_states.front();
        new_states.pop();
        std::cout << p.first << " " << p.second << std::endl;
        std::cout << (p.second != nullptr) << std::endl;
        if (p.second != nullptr) {
            state.push_back(p.second);
        } else if (p.first == -1) {
            state.pop_back();
        } else {
            while ((int)state.size() > p.first) {
                std::cout << "desired size is " << p.first << std::endl;
                std::cout << "current size: " << state.size() << std::endl;
                state.pop_back();
                std::cout << "popped one" << std::endl;
            }
        }
    }
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
            new_states.push(std::make_pair(0, std::make_shared<MainMenu>(*this)));
            break;
        case GameStateType::PauseMenu:
            new_states.push(std::make_pair(0, std::make_shared<Pause>(*this)));
            break;
        case GameStateType::MainOptionsMenu:
            new_states.push(std::make_pair(0, std::make_shared<MainOptionsMenu>(*this)));
            break;
        case GameStateType::World:
            new_states.push(std::make_pair(0, std::make_shared<World>(*this)));
            break;
    }
}

void Game::popState(int to_size) {
    new_states.push(std::make_pair(to_size, nullptr));
}

GameState::GameState(Game &g) : parent{g}, window{g.getWindow()}, ih{std::make_unique<InputHandler>(g)} {}

void GameState::setKeymap(Keymap keymap) {
    ih->setKeymap(keymap);
}

void GameState::handleInput() {
    std::vector< std::shared_ptr<Command> > input = ih->handleInput(window);
    for (std::shared_ptr<Command> c : input) {
        c->execute();
    }
}
