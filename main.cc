#include "game.h"

int main() {
    Game G;

    while (!G.isFinished()) {
        G.handleInput();
        G.update();
        G.draw();
    }
}
