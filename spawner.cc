#include <vector>
#include <cmath>
#include "spawner.h"
#include "bullet.h"
#include "data.h"
#include "bullet_path.h"

std::vector<Bullet*> Spawners::AAA::get_bullets(int frame) {
    (void)frame;

    std::vector<Bullet*> bullets;
    Bullet *b = new Bullet{loc, p, 5.0, false};
    bullets.push_back(b);
    return bullets;
}

std::vector<Bullet*> Spawners::BoWaP::get_bullets(int frame) {
    std::vector<Bullet*> bullets;
    if (frame % period == 0) {
        for (int i = 0; i < 6; i++) {
            Bullet *b = new Bullet{loc, new Paths::ThetaMag{theta, mag}, 5.0, true};
            bullets.push_back(b);
            theta += 2.0*PI/num_branches;
        }

        theta = theta + vel;
        vel += acc;
    }
    return bullets;
}

std::vector<Bullet*> Spawners::NotBoWaP::get_bullets(int frame) {
    std::vector<Bullet*> bullets;
    if (frame % period == 0) {
        for (int i = 0; i < 6; i++) {
            Bullet *b = new Bullet{loc, new Paths::ThetaMag{theta+(i/3.0)*PI, mag}, 5.0, true};
            bullets.push_back(b);
        }

        theta = theta + vel;
        vel += sin(frame)/6;
    }
    return bullets;
}
