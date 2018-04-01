#include "bullet.h"
#include "player.h"
#include "bullet_path.h"

Player::Player() : Drawable{ { { "resources/textures/players/reimu/back.png" } } } {
    hitbox_radius = PLAYER_HITBOX_RADIUS;
    p = new Paths::ThetaMag{-PI/2.0, 10};
}

Player::~Player() {
    delete p;
}

void Player::move(Vec2 vel) {
    loc += vel;
}

std::vector<Bullet*> Player::get_bullets(int frame) {
    std::vector<Bullet*> bullets;
    if (frame % 3 == 0) {
        Bullet *b = new Bullet{loc, p};
        bullets.push_back(b);
    }
    return bullets;
}
