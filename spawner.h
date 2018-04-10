#ifndef __SPAWNER_H_
#define __SPAWNER_H_

#include <vector>
#include "movable.h"
#include "data.h"

class Bullet;
class Path;

class Spawner : public Movable {
public:
    Spawner() {}
    virtual ~Spawner() = default;
    virtual std::vector< std::shared_ptr<Bullet> > getBullets(int) = 0;
    virtual bool isFinished() { return false; }
};

namespace Spawners {
    class Spread : public Spawner {
        double spread;
        double angle;
        double mag;
        int shots;
        int delay;
        int times;
        int num_shot;
        int next_shot;
        std::vector< std::shared_ptr<Path> > p;
    public:
        Spread(double spread=2*PI, double angle=0, double mag=5, int shots=3, int delay=5, int times=5);
        std::vector< std::shared_ptr<Bullet> > getBullets(int) override;
        bool isFinished() override;
    };
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
