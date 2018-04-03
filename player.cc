#include "bullet.h"
#include "player.h"
#include "path.h"

Player::Player() : Drawable{ { { "resources/textures/players/reimu/back.png" } } } {
    hitbox_radius = PLAYER_HITBOX_RADIUS;
    p = std::make_shared<Paths::ThetaMag>(-PI/2.0, 10);
}

void Player::move(Vec2 vel) {
    loc += vel;
}

std::vector< std::shared_ptr<Bullet> > Player::get_bullets(int frame) {
    std::vector< std::shared_ptr<Bullet> > bullets;
    if (frame % 3 == 0) {
        bullets.push_back(std::make_shared<Bullet>(loc,p));;
    }
    return bullets;
}
