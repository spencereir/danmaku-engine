#ifndef __INPUT_H_
#define __INPUT_H_

#include <SFML/Graphics.hpp>
#include "data.h"

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class Game;

class InputHandler {
    Game &g;
    Keymap keymap;
public:
    InputHandler(Game &g) : g{g} {}
    void setKeymap(Keymap _keymap) { keymap = _keymap; }
    std::vector< std::shared_ptr<Command> > handleInput(sf::RenderWindow &w);
};

class Menu;
class OptionsMenu;
class World;
class Player;

namespace Commands {
    namespace Menu {
        class CursorUp : public Command {
            ::Menu &menu;
        public:
            CursorUp(::Menu& menu) : menu{menu} {}
            void execute();
        };
        class CursorDown : public Command {
            ::Menu &menu;
        public:
            CursorDown(::Menu& menu) : menu{menu} {}
            void execute();
        };
        class Select : public Command {
            ::Menu &menu;
        public:
            Select(::Menu& menu) : menu{menu} {}
           void execute();
        };
    };

    namespace OptionsMenu {
        class CursorUp : public Command {
            ::OptionsMenu &menu;
        public:
            CursorUp(::OptionsMenu& menu) : menu{menu} {}
            void execute();
        };
        class CursorDown : public Command {
            ::OptionsMenu &menu;
        public:
            CursorDown(::OptionsMenu& menu) : menu{menu} {}
            void execute();
        };
        class CursorLeft : public Command {
            ::OptionsMenu &menu;
        public:
            CursorLeft(::OptionsMenu& menu) : menu{menu} {}
            void execute();
        };
        class CursorRight : public Command {
            ::OptionsMenu &menu;
        public:
            CursorRight(::OptionsMenu& menu) : menu{menu} {}
            void execute();
        };
        class Select : public Command {
            ::OptionsMenu &menu;
        public:
            Select(::OptionsMenu& menu) : menu{menu} {}
           void execute();
        };
    };

    namespace Player {
        class MoveUp : public Command {
            ::World &world;
            ::Player &player;
            double vel;
        public:
            MoveUp(::World &world, ::Player &player, double vel) : world{world}, player{player}, vel{vel} {}
            void execute();
        };
        class MoveDown : public Command {
            ::World &world;
            ::Player &player;
            double vel;
        public:
            MoveDown(::World &world, ::Player &player, double vel) : world{world}, player{player}, vel{vel} {}
            void execute();
        };
        class MoveLeft : public Command {
            ::World &world;
            ::Player &player;
            double vel;
        public:
            MoveLeft(::World &world, ::Player &player, double vel) : world{world}, player{player}, vel{vel} {}
            void execute();
        };
        class MoveRight : public Command {
            ::World &world;
            ::Player &player;
            double vel;
        public:
            MoveRight(World &world, ::Player &player, double vel) : world{world}, player{player}, vel{vel} {}
            void execute();
        };
        class Shoot : public Command {
            ::World &world;
            ::Player &player;
        public:
            Shoot(World &world, ::Player &player) : world{world}, player{player} {}
            void execute();
        };
        class Bomb : public Command {
            ::World &world;
            ::Player &player;
        public:
            Bomb(World &world, ::Player &player) : world{world}, player{player} {}
            void execute();
        };
    };

    namespace World {
        class Pause : public Command {
            ::World &world;
        public:
            Pause(::World &world) : world{world} {}
            void execute();
        };
    };
};

#endif
