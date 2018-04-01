#include "data.h"
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>

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
        } else if (option_name == "wINDOW_TITLE") {
            ret.WINDOW_TITLE = ss.str();
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
