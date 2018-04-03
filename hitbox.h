#ifndef __HITBOX_H_
#define __HITBOX_H_

#include <utility>
#include "data.h"

typedef std::pair< Vec2, double > Hitbox;

bool intersect(Hitbox hitbox_1, Hitbox hitbox_2);

#endif
