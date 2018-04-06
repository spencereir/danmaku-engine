#include "clock.h"

sf::Time Clock::getElapsedTime() {
    return clock.getElapsedTime() - pause_time;
}

sf::Time Clock::lap() {
    sf::Time ret = clock.getElapsedTime() - lap_time;
    lap_time = clock.getElapsedTime();
    return ret;
}

void Clock::restart() {
    pause_time = sf::Time{};
    lap_time = sf::Time{};
    clock = sf::Clock{};
    pause_clock = sf::Clock{};
}

void Clock::pause() {
    pause_clock.restart();
}

void Clock::resume() {
    sf::Time t = pause_clock.getElapsedTime();
    pause_time += t;
    lap_time += t;
}
