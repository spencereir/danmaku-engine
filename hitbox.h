#ifndef __HITBOX_H_
#define __HITBOX_H_

#include <utility>
#include "data.h"

bool intersect(std::pair< Vec2, double > hitbox_1, std::pair< Vec2, double > hitbox_2);

#endif
