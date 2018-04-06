#ifndef __CLOCK_H_
#define __CLOCK_H_

#include <SFML/Graphics.hpp>

class Clock {
    sf::Time lap_time, pause_time;
    sf::Clock clock, pause_clock;
public:
    sf::Time getElapsedTime();
    sf::Time lap();
    void restart();
    void pause();
    void resume();
};

#endif
