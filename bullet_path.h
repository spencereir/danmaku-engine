#ifndef __BULLET_PATH_
#define __BULLET_PATH_

#include "data.h"

class BulletPath {
public:
    virtual ~BulletPath() = default;
    virtual Vec2 loc(int t) = 0;
};

namespace Paths {
    class ThetaMag : public BulletPath {
        Vec2 v;
    public:
        ThetaMag(double theta, double mag) : v{mag * cos(theta), mag * sin(theta)} {}
        Vec2 loc(int t) override;
    };
    class VelAcc : public BulletPath {
        Vec2 vel, acc;
    public:
        VelAcc(Vec2 vel, Vec2 acc) : vel{vel}, acc{acc} {}
        Vec2 loc(int t) override;
    };
};

#endif
