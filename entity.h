#ifndef __ENTITY_H_
#define __ENTITY_H_

#include "data.h"

// An entity is an object with location in the world
class Entity {
    Vec2 loc;
public:
    Entity(Vec2 loc={0,0}) : loc{loc} {}
    virtual Vec2 &getLocation() { return loc; }
    virtual void setLocation(Vec2 _loc) { loc = _loc; }
};

#endif
