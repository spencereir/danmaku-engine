#ifndef __DATA_H_
#define __DATA_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <vector>
#include <utility>
#include <memory>

const double PLAYER_HITBOX_RADIUS = 8;
const double DEFAULT_BULLET_HITBOX_RADIUS = 8;
const double PI = 3.14159265;
const double TOLERANCE = 1e-5;

class Command;
typedef std::vector< std::tuple< std::vector< sf::Keyboard::Key >, std::vector< sf::Keyboard::Key >, std::shared_ptr< Command >  > > Keymap;

enum class GameStateType {
    MainMenu,
    PauseMenu,
    MainOptionsMenu,
    World
};

struct Options {
    int SCREEN_WIDTH = 800;
    int SCREEN_HEIGHT = 600;
    int FRAME_LIMIT = 60;
    std::string WINDOW_TITLE = "Bullet Hell Demo";
};

Options loadOptionsFromFile(std::string);

// Vec2
struct Vec2 {
    double x;
    double y;
    Vec2(double x=0, double y=0) : x{x}, y{y} {}
    bool operator==(const Vec2 &other) {
        return (fabs(other.x - x) <= TOLERANCE && fabs(other.y - y) <= TOLERANCE);
    }
    bool operator!=(const Vec2 &other) {
        return (other.x != x || other.y != y);
    }
    Vec2 operator+(const Vec2 &other) {
        return Vec2{x + other.x, y + other.y};
    }
    Vec2 operator-(const Vec2 &other) {
        return Vec2{x - other.x, y - other.y};
    }
    Vec2 operator*(const double factor) {
        return Vec2{factor * x, factor * y};
    }
    Vec2 operator/(const double factor) {
        return Vec2{x/factor, y/factor};
    }
    Vec2 &operator+=(const Vec2 &other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vec2 &operator-=(const Vec2 &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vec2 &operator*=(double factor) {
        x *= factor;
        y *= factor;
        return *this;
    }
    Vec2 &operator/=(double factor) {
        x /= factor;
        y /= factor;
        return *this;
    }
};

Vec2 from_mag_theta(double, double);
double magnitude(Vec2);

#endif
