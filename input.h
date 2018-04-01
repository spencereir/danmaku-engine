#ifndef __INPUT_H_
#define __INPUT_H_

#include <SFML/Graphics.hpp>
#include "data.h"

/* Factory to build commands given parent information; execute takes no params, operates directly on objects passed at construction
 * GameState constructor registers itself and children to an input handler with appropriate keybindings
 * InputHandler takes SFML window, list of keybindings/commands, executes commands satisfied by keybindings
 * Keybindings are stored as two lists, modifier keys + action keys
 * Modifier keys are not debounced, are checked as isKeyPressed instead of in the event loop
 * e.g., menu initialier could look like
[...] ih = new InputHandler{
    { {sf::Keyboard::LShift}, {sf::Keyboard::Down}, new Commands::Menu::CursorDown{this}
}
 */

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};


class InputHandler {
    Keymap keymap;
public:
    void setKeymap(Keymap _keymap) { keymap = _keymap; }
    std::vector< Command* > handleInput(sf::RenderWindow *w);
};


class Menu;
class OptionsMenu;
class World;
class Player;

namespace Commands {
    namespace Menu {
        class CursorUp : public Command {
            ::Menu *menu;
        public:
            CursorUp(::Menu* menu) : menu{menu} {}
            void execute();
        };
        class CursorDown : public Command {
            ::Menu *menu;
        public:
            CursorDown(::Menu* menu) : menu{menu} {}
            void execute();
        };
        class Select : public Command {
            ::Menu *menu;
        public:
            Select(::Menu* menu) : menu{menu} {}
           void execute();
        };
    };

    namespace OptionsMenu {
        class CursorUp : public Command {
            ::OptionsMenu *menu;
        public:
            CursorUp(::OptionsMenu* menu) : menu{menu} {}
            void execute();
        };
        class CursorDown : public Command {
            ::OptionsMenu *menu;
        public:
            CursorDown(::OptionsMenu* menu) : menu{menu} {}
            void execute();
        };
        class CursorLeft : public Command {
            ::OptionsMenu *menu;
        public:
            CursorLeft(::OptionsMenu* menu) : menu{menu} {}
            void execute();
        };
        class CursorRight : public Command {
            ::OptionsMenu *menu;
        public:
            CursorRight(::OptionsMenu* menu) : menu{menu} {}
            void execute();
        };
        class Select : public Command {
            ::OptionsMenu *menu;
        public:
            Select(::OptionsMenu* menu) : menu{menu} {}
           void execute();
        };
    };

    namespace Player {
        class MoveUp : public Command {
            ::World *world;
            ::Player *player;
            double vel;
        public:
            MoveUp(::World *world, ::Player *player, double vel) : world{world}, player{player}, vel{vel} {}
            void execute();
        };
        class MoveDown : public Command {
            ::World *world;
            ::Player *player;
            double vel;
        public:
            MoveDown(::World *world, ::Player *player, double vel) : world{world}, player{player}, vel{vel} {}
            void execute();
        };
        class MoveLeft : public Command {
            ::World *world;
            ::Player *player;
            double vel;
        public:
            MoveLeft(::World *world, ::Player *player, double vel) : world{world}, player{player}, vel{vel} {}
            void execute();
        };
        class MoveRight : public Command {
            ::World *world;
            ::Player *player;
            double vel;
        public:
            MoveRight(World *world, ::Player *player, double vel) : world{world}, player{player}, vel{vel} {}
            void execute();
        };
    };
};

#endif
