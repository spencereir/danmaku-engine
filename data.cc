#include "data.h"
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>

std::ostream &operator<<(std::ostream &o, const Options &opt) {
    o << "# Automatically generated config file by game"
      << "\nSCREEN_WIDTH " << opt.SCREEN_WIDTH
      << "\nSCREEN_HEIGHT " << opt.SCREEN_HEIGHT
      << "\nFRAME_LIMIT " << opt.FRAME_LIMIT
      << "\nFRAME_SYNC " << opt.FRAME_SYNC
      << "\nREF_FRAME " << opt.REF_FRAME
      << "\nWINDOW_TITLE " << opt.WINDOW_TITLE
      << "\n";
    return o;
}

Options loadOptionsFromFile(std::string filename) {
    std::ifstream fin{filename};
    std::string s;
    Options ret = Options{};
    while (std::getline(fin, s)) {
        if (s.empty() || s[0] == '#')
            continue;

        std::stringstream ss{s};
        std::string option_name;
        ss >> option_name;
        if (option_name == "SCREEN_WIDTH") {
            ss >> ret.SCREEN_WIDTH;
        } else if (option_name == "SCREEN_HEIGHT") {
            ss >> ret.SCREEN_HEIGHT;
        } else if (option_name == "FRAME_LIMIT") {
            ss >> ret.FRAME_LIMIT;
        } else if (option_name == "WINDOW_TITLE") {
            ret.WINDOW_TITLE = ss.str();
        } else if (option_name == "FRAME_SYNC") {
            ss >> ret.FRAME_SYNC;
        } else if (option_name == "REF_FRAME") {
            ss >> ret.REF_FRAME;
        }
    }
    return ret;
}

Vec2 from_mag_theta(double mag, double theta) {
    return Vec2{mag * cos(theta), mag * sin(theta)};
}

double magnitude(Vec2 v) {
    return sqrt(v.x*v.x+v.y*v.y);
}
