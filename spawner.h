#ifndef __SPAWNER_H_
#define __SPAWNER_H_

#include <vector>
#include "data.h"
#include "bullet_path.h"

class Bullet;

class Spawner {
protected:
    Vec2 loc;
public:
    virtual ~Spawner() = default;
    Vec2 getLocation() { return loc; }
    void setLocation(Vec2 _loc) { loc = _loc; }
    virtual std::vector<Bullet*> get_bullets(int) = 0;
};

namespace Spawners {
    class AimedGun : public Spawner {
        double mag;
        int period;

    public:
        AimedGun(double mag=1, int period=5) : mag{mag}, period{period} {}
        std::vector<Bullet*> get_bullets(int) override;
    };

    class AAA : public Spawner {
        double vel = 5;
        double theta = 0;
        double mag;
        int period;
        BulletPath *p;

    public:
        AAA(double mag=1, int period=5) : mag{mag}, period{period}, p{new Paths::ThetaMag{0,5}} {}
        std::vector<Bullet*> get_bullets(int) override;
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
        std::vector<Bullet*> get_bullets(int) override;
    };

    class NotBoWaP : public Spawner {
        double vel = 5;
        double theta = 0;
        double mag;
        double magacc;
        int period;

    public:
        NotBoWaP(double mag=1, double magacc=0.1, int period=5) : mag{mag}, magacc{magacc}, period{period} {}
        std::vector<Bullet*> get_bullets(int) override;
    };
};

#endif
