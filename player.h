#ifndef __PLAYER_H_
#define __PLAYER_H_

#include <vector>
#include "data.h"
#include "drawable.h"

class Bullet;
class BulletPath;

class Player : public Drawable {
    double hitbox_radius;
    Vec2 loc;
    BulletPath *p;

public:
    Player();
    virtual ~Player();
    Vec2 getLocation() { return loc; }
    double getHitboxRadius() { return hitbox_radius; }
    void setLocation(Vec2 _loc) { loc = _loc; }
    void move(Vec2);
    std::vector<Bullet*> get_bullets(int);
};

#endif
