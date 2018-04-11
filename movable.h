#ifndef __MOVABLE_H_
#define __MOVABLE_H_

#include "entity.h"

// A Movable is an Entity that can be moved
// It augments Entity by adding velocity, acceleration, and additionally
// adds a move() function taking frames to move
class Movable : public virtual Entity {
    Vec2 vel, acc;
public:
    Movable(Vec2 loc={0,0}, Vec2 vel={0,0}, Vec2 acc={0,0}) : Entity{loc}, vel{vel}, acc{acc} {}
    Vec2 &getVelocity() { return vel; }
    Vec2 &getAcceleration() { return acc; }
    void setVelocity(Vec2 _vel) { vel = _vel; }
    void setAcceleration(Vec2 _acc) { acc = _acc; }
    virtual void move(double frames) { Vec2 &loc = getLocation(); loc += vel*frames; vel += acc*frames; }
};

#endif
