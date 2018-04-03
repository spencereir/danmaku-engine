#ifndef __PATH_H_
#define __PATH_H_

#include "data.h"

class Path {
public:
    virtual ~Path() = default;
    virtual Vec2 loc(int t) = 0;
};

namespace Paths {
    class ThetaMag : public Path {
        Vec2 v;
    public:
        ThetaMag(double theta, double mag) : v{mag * cos(theta), mag * sin(theta)} {}
        Vec2 loc(int t) override;
    };
    class VelAcc : public Path {
        Vec2 vel, acc;
    public:
        VelAcc(Vec2 vel, Vec2 acc) : vel{vel}, acc{acc} {}
        Vec2 loc(int t) override;
    };
};

#endif
