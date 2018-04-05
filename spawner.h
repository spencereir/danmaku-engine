#ifndef __SPAWNER_H_
#define __SPAWNER_H_

#include <vector>
#include "data.h"

class Bullet;

class Spawner {
protected:
    Vec2 loc;
public:
    virtual ~Spawner() = default;
    Vec2 getLocation() { return loc; }
    void setLocation(Vec2 _loc) { loc = _loc; }
    virtual std::vector< std::shared_ptr<Bullet> > getBullets(int) = 0;
};

namespace Spawners {
    class BoWaP : public Spawner {
        double theta;
        double mag;
        double vel;
        double acc;
        double num_branches;
        int period;

    public:
        BoWaP(double mag=1, double num_branches=6, double acc=0.1, int period=5) : theta{0}, mag{mag}, vel{0}, acc{acc}, num_branches{num_branches}, period{period} {}
        std::vector< std::shared_ptr<Bullet> > getBullets(int) override;
    };
};

#endif
