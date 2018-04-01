#include "hitbox.h"
#include "data.h"

bool intersect(std::pair< Vec2, double > hitbox_1, std::pair< Vec2, double > hitbox_2) {
    return magnitude(hitbox_1.first - hitbox_2.first) < hitbox_1.second + hitbox_2.second;
}
