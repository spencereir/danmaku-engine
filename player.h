#ifndef __PLAYER_H_
#define __PLAYER_H_

#include <vector>
#include <memory>
#include "data.h"
#include "drawable.h"

class Bullet;
class Path;

class Player : public Drawable {
    double hitbox_radius;
    Vec2 loc;
    std::shared_ptr<Path> p;

public:
    Player();
    virtual ~Player() = default;
    Vec2 getLocation() { return loc; }
    double getHitboxRadius() { return hitbox_radius; }
    void setLocation(Vec2 _loc) { loc = _loc; }
    void move(Vec2);
    std::vector< std::shared_ptr<Bullet> > get_bullets(int);
};

#endif
