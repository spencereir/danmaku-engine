#include "hitbox.h"
#include "data.h"

bool intersect(Hitbox hitbox_1, Hitbox hitbox_2) {
    return magnitude(hitbox_1.first - hitbox_2.first) < hitbox_1.second + hitbox_2.second;
}
