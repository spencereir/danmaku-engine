#include "bullet.h"
#include "player.h"
#include "path.h"

Player::Player() : Drawable{ { { "resources/textures/players/reimu/back.png" } } } {
    hitbox_radius = PLAYER_HITBOX_RADIUS;
    p = std::make_shared<Paths::ThetaMag>(-PI/2.0, 10);
}

std::vector< std::shared_ptr<Bullet> > Player::getBullets() {
    std::vector< std::shared_ptr<Bullet> > bullets;
    bullets.push_back(std::make_shared<Bullet>(getLocation(),p));;
    return bullets;
}
