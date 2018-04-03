#include "bullet.h"
#include "data.h"
#include "path.h"
#include <string>

Bullet::Bullet(Vec2 loc, std::shared_ptr<Path> p, double radius) : Drawable{
    { {"resources/textures/bullets/red/circle-1.png"},
      {"resources/textures/bullets/orange/circle-1.png"},
      {"resources/textures/bullets/yellow/circle-1.png"},
      {"resources/textures/bullets/green/circle-1.png"},
      {"resources/textures/bullets/blue/circle-1.png"},
      {"resources/textures/bullets/purple/circle-1.png"} } },
    p{p}, loc{loc}, lifetime{0}, cache_time{-1}, hitbox_radius{radius} {}

Vec2 Bullet::getLocation() {
    if (cache_time == lifetime) return loc_cache;
    cache_time = lifetime;
    auto x =  p->loc(lifetime);
    loc_cache = loc + x;
    return loc_cache = loc + x;
}
