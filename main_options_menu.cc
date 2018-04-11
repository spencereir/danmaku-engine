#include "main_options_menu.h"
#include <fstream>

MainOptionsMenu::MainOptionsMenu(Game &g) : OptionsMenu{g} {
    cursor = 0;
    menu_option = {"Frame Sync", "Frame Rate", "Resolution"};
    subcursor = {parent.getOptions().FRAME_SYNC ? 0 : 1,
                 parent.getOptions().FRAME_LIMIT == 30 ? 0 :
                     (parent.getOptions().FRAME_LIMIT == 60 ? 1 : 2),
                 0, 0};
    submenu_option = {{"ON", "OFF"}, {"30", "60", "90"}, {"640x480", "800x600"}, {"Save", "Default"}};
}

void MainOptionsMenu::select() {
    if (cursor == (int)submenu_option.size()-1) {
        if (subcursor[cursor] == 0) {
            // save
            Options new_options;
            new_options.FRAME_SYNC = (subcursor[0] == 0);
            new_options.FRAME_LIMIT = 30*(subcursor[1]+1);
            new_options.SCREEN_WIDTH = (subcursor[2] == 0 ? 640 : 800);
            new_options.SCREEN_HEIGHT = (subcursor[2] == 0 ? 480 : 600);
            std::ofstream fout{"game.conf", std::ofstream::out};
            fout << new_options;
            parent.reloadOptions("game.conf");
            parent.popState();
        } else {
            subcursor = {0, 1, 1, 0};
        }
    } else {
        // pop up tooltip?
    }
}

void MainOptionsMenu::draw() {
    window.clear();
    OptionsMenu::draw();
    window.display();
}
