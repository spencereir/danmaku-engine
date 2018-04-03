#include <vector>
#include <memory>
#include <cmath>
#include "spawner.h"
#include "bullet.h"
#include "data.h"
#include "path.h"

std::vector< std::shared_ptr<Bullet> > Spawners::BoWaP::get_bullets(int frame) {
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
