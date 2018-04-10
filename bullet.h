#ifndef __BULLET_H_
#define __BULLET_H_

#include <SFML/Graphics.hpp>
#include <memory>
#include "drawable.h"
#include "movable.h"
#include "data.h"

class Path;

class Bullet : public Drawable, public Movable {
    Vec2 initial_loc;
    std::shared_ptr<Path> p;
    double lifetime;
    bool manage_path;
    Vec2 loc_cache;
    int cache_time;
    double hitbox_radius;

public:
    Bullet(Vec2, std::shared_ptr<Path>, double=DEFAULT_BULLET_HITBOX_RADIUS);
    virtual ~Bullet() = default;
    Vec2 &getLocation() override;
    double getHitboxRadius() { return hitbox_radius; }
    void move(double frame) override { lifetime += frame; }
    void setHitboxRadius(double);
};

enum class BulletType {
    RED_CIRCLE_1,
    ORANGE_CIRCLE_1,
    YELLOW_CIRCLE_1,
    GREEN_CIRCLE_1,
    BLUE_CIRCLE_1,
    PURPLE_CIRCLE_1
};

#endif
