#ifndef __GAME_H_
#define __GAME_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "data.h"

class Game;
class Command;
class InputHandler;

class GameState {
protected:
    Game *parent;
    sf::RenderWindow *window;
    InputHandler *ih;

public:
    GameState(Game*);
    virtual ~GameState();
    void setKeymap(Keymap);
    virtual void handleInput();
    virtual void update() = 0;
    virtual void draw() = 0;
};

class Game {
    Options options;
    sf::RenderWindow *window;
    bool finished;
    std::vector<GameState*> state;

public:
    Game(std::string="game.conf");
    ~Game();
    sf::RenderWindow *getWindow() { return window; }
    void handleInput();
    void update();
    void draw();

    // Game state functions
    void pushState(GameState *g) { state.push_back(g); }
    void popState(int=-1);

    bool isFinished() { return finished; }
};

#endif
