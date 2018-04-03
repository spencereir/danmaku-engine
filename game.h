#ifndef __GAME_H_
#define __GAME_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "data.h"
#include "input.h"

class Game;
class InputHandler;

class GameState {
protected:
    Game &parent;
    sf::RenderWindow &window;
    std::unique_ptr<InputHandler> ih;

public:
    GameState(Game&);
    virtual ~GameState() = default;
    Game &getParent() { return parent; }
    void setKeymap(Keymap);
    virtual void handleInput();
    virtual void update() = 0;
    virtual void draw() = 0;
};

class Game {
    Options options;
    sf::RenderWindow window;
    bool finished;
    std::vector< std::shared_ptr< GameState > > state;

public:
    Game(std::string="game.conf");
    ~Game();
    sf::RenderWindow &getWindow() { return window; }
    void handleInput();
    void update();
    void draw();

    // Game state functions
    void pushState(GameStateType);
    void popState(int=-1);

    bool isFinished() { return finished; }
};

#endif
