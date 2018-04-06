#include <vector>
#include <memory>
#include <cmath>
#include "spawner.h"
#include "bullet.h"
#include "data.h"
#include "path.h"

Spawners::Spread::Spread(double spread, double angle, double mag, int shots, int delay, int times) :
    spread{spread}, angle{angle}, mag{mag}, shots{shots}, delay{delay}, times{times}, num_shot{0}, next_shot{-1} {
    p.resize(shots);
    for (int i = 0; i < shots; i++) {
        double theta = spread/shots * (i - shots/2.0) + angle;
        p[i] = std::make_shared<Paths::ThetaMag>(theta, mag);
    }
}

std::vector< std::shared_ptr<Bullet> > Spawners::Spread::getBullets(int frame) {
    std::vector< std::shared_ptr<Bullet> > bullets;
    if (next_shot == -1) next_shot = frame;
    if (frame >= next_shot) {
        for (int i = 0; i < shots; i++) {
            bullets.push_back(std::make_shared<Bullet>(loc, p[i]));
        }
        next_shot += delay;
        num_shot++;
    }
    return bullets;
}

bool Spawners::Spread::isFinished() {
    return num_shot >= times;
}

std::vector< std::shared_ptr<Bullet> > Spawners::BoWaP::getBullets(int frame) {
    std::vector< std::shared_ptr<Bullet> > bullets;
    if (frame % period == 0) {
        for (int i = 0; i < 6; i++) {
            bullets.push_back(std::make_shared<Bullet>(loc, std::make_shared<Paths::ThetaMag>(theta, mag), 5.0));
            theta += 2.0*PI/num_branches;
        }

        theta = theta + vel;
        vel += acc;
    }
    return bullets;
}
