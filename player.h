#ifndef __PLAYER_H_
#define __PLAYER_H_

#include <vector>
#include <memory>
#include "data.h"
#include "drawable.h"
#include "movable.h"

class Bullet;
class Path;

class Player : public Drawable, public Movable {
    double hitbox_radius;
    std::shared_ptr<Path> p;

public:
    Player();
    virtual ~Player() = default;
    double getHitboxRadius() { return hitbox_radius; }
    std::vector< std::shared_ptr<Bullet> > getBullets();
};

#endif
