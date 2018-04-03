#include <vector>
#include "world.h"
#include "resources.h"
#include "spawner.h"
#include "bullet.h"
#include "player.h"
#include "game.h"
#include "pause.h"
#include "hitbox.h"
#include "input.h"

World::World(Game *g) : GameState{g}, player{new Player}  {
    player_vel = 5.0;
    double focus_vel = 2.0;

    setKeymap({
        { {sf::Keyboard::Left}, {}, new Commands::Player::MoveLeft{this, player, player_vel}},
        { {sf::Keyboard::Right}, {}, new Commands::Player::MoveRight{this, player, player_vel}},
        { {sf::Keyboard::Up}, {}, new Commands::Player::MoveUp{this, player, player_vel}},
        { {sf::Keyboard::Down}, {}, new Commands::Player::MoveDown{this, player, player_vel}},
        { {sf::Keyboard::LShift, sf::Keyboard::Left}, {}, new Commands::Player::MoveLeft{this, player, focus_vel-player_vel}},
        { {sf::Keyboard::LShift, sf::Keyboard::Right}, {}, new Commands::Player::MoveRight{this, player, focus_vel-player_vel}},
        { {sf::Keyboard::LShift, sf::Keyboard::Up}, {}, new Commands::Player::MoveUp{this, player, focus_vel-player_vel}},
        { {sf::Keyboard::LShift, sf::Keyboard::Down}, {}, new Commands::Player::MoveDown{this, player, focus_vel-player_vel}}
    });

    player->setLocation({100,900});
    Spawner *s = new Spawners::BoWaP{1, 6, 0.05, 3};
    s->setLocation({300,200});
    player_vel = 5;
    registerSpawner(s);
}

World::~World() {
    while (!spawner.empty()) {
        delete spawner.back();
        spawner.pop_back();
    }
    while (!bullet.empty()) {
        delete bullet.back();
        bullet.pop_back();
    }
    while (!player_bullet.empty()) {
        delete player_bullet.back();
        player_bullet.pop_back();
    }
    delete player;
}

void World::registerBullet(Bullet *b) {
    bullet.push_back(b);
}

void World::registerPlayerBullet(Bullet *b) {
    player_bullet.push_back(b);
}

void World::registerSpawner(Spawner *s) {
    spawner.push_back(s);
}

void World::moveBullets() {
    std::vector<Bullet*> new_bullets;
    for (Bullet *b : bullet) {
        b->move();
        if (b->getLocation().x >= -10 && b->getLocation().x <= 1000 && b->getLocation().y >= -10 && b->getLocation().y <= 1200) {
            new_bullets.push_back(b);
        } else {
            delete b;
        }
    }
    bullet = new_bullets;

    new_bullets.clear();
    for (Bullet *b : player_bullet) {
        b->move();
        if (b->getLocation().y < 0)
            delete b;
        else
            new_bullets.push_back(b);
    }
    player_bullet = new_bullets;
}

void World::spawnBullets() {
    for (Spawner *s : spawner) {
        for (Bullet *b : s->get_bullets(frame)) {
            registerBullet(b);
        }
    }
}

void World::spawnPlayerBullets() {
    for (Bullet *b : player->get_bullets(frame)) {
        registerPlayerBullet(b);
    }
}

void World::checkCollisions() {
    for (Bullet *b : bullet) {
        if (intersect({b->getLocation(), b->getHitboxRadius()}, {player->getLocation(), player->getHitboxRadius()})) {
            parent->popState(1);
            return;
        }
    }
}

void World::update() {
    frame++;
    moveBullets();
    spawnBullets();
    checkCollisions();
}

void World::draw() {
    window->clear();
    for (Bullet *b : bullet) {
        b->draw(window);
    }
    for (Bullet *b : player_bullet) {
        b->draw(window);
    }

    player->draw(window);
    window->display();
}
