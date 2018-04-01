#ifndef __BULLET_H_
#define __BULLET_H_

#include "drawable.h"
#include "data.h"
#include <SFML/Graphics.hpp>

class BulletPath;

class Bullet : public Drawable {
    BulletPath *p;
    Vec2 loc;
    int lifetime;
    bool manage_path;
    Vec2 loc_cache;
    int cache_time;
    double hitbox_radius;

public:
    Bullet(Vec2, BulletPath*, double=DEFAULT_BULLET_HITBOX_RADIUS, bool=false);
    virtual ~Bullet();
    Vec2 getLocation();
    double getHitboxRadius() { return hitbox_radius; }
    void move() { lifetime++; }
    void setHitboxRadius(double);
};

#endif
