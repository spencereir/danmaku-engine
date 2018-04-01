#ifndef __INPUT_H_
#define __INPUT_H_

class Command {
public:
    virtual ~Command();
    virtual void execute(GameState*) = 0;
};

class InputHandler {
    std::vector< std::pair< std::vector< sf::Keyboard::Key >, Command* > > keymap;
public:
    InputHandler(std::vector< std::pair< std::vector< sf::Keyboard::Key >, Command* > > keymap) : keymap{keymap} {}
    std::vector< Command* > handleInput();
};

#endif
