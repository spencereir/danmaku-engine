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

World::World(Game &g) : GameState{g}, player{std::make_unique<Player>()} {
    player_vel = 5.0;
    double focus_vel = 2.0;

    setKeymap({
        { {sf::Keyboard::Left}, {}, std::make_shared<Commands::Player::MoveLeft>(*this, *player, player_vel)},
        { {sf::Keyboard::Right}, {}, std::make_shared<Commands::Player::MoveRight>(*this, *player, player_vel)},
        { {sf::Keyboard::Up}, {}, std::make_shared<Commands::Player::MoveUp>(*this, *player, player_vel)},
        { {sf::Keyboard::Down}, {}, std::make_shared<Commands::Player::MoveDown>(*this, *player, player_vel)},
        { {sf::Keyboard::LShift, sf::Keyboard::Left}, {}, std::make_shared<Commands::Player::MoveLeft>(*this, *player, focus_vel-player_vel)},
        { {sf::Keyboard::LShift, sf::Keyboard::Right}, {}, std::make_shared<Commands::Player::MoveRight>(*this, *player, focus_vel-player_vel)},
        { {sf::Keyboard::LShift, sf::Keyboard::Up}, {}, std::make_shared<Commands::Player::MoveUp>(*this, *player, focus_vel-player_vel)},
        { {sf::Keyboard::LShift, sf::Keyboard::Down}, {}, std::make_shared<Commands::Player::MoveDown>(*this, *player, focus_vel-player_vel)},
        { {sf::Keyboard::Z}, {}, std::make_shared<Commands::Player::Shoot>(*this, *player)},
        { {sf::Keyboard::X}, {}, std::make_shared<Commands::Player::Bomb>(*this, *player)},
        { {}, {sf::Keyboard::Escape}, std::make_shared<Commands::World::Pause>(*this)}
    });

    player->setLocation({100,900});
    std::shared_ptr<Spawner> s = std::make_shared<Spawners::BoWaP>(1, 6, 0.05, 3);
    s->setLocation({300,200});
    player_vel = 5;
    registerSpawner(s);
}

void World::registerBullet(std::shared_ptr<Bullet> b) {
    bullet.push_back(b);
}

void World::registerPlayerBullet(std::shared_ptr<Bullet> b) {
    player_bullet.push_back(b);
}

void World::registerSpawner(std::shared_ptr<Spawner> s) {
    spawner.push_back(s);
}

void World::moveBullets() {
    std::vector< std::shared_ptr<Bullet> > new_bullets;
    for (std::shared_ptr<Bullet> b : bullet) {
        b->move();
        if (b->getLocation().x >= -10 && b->getLocation().x <= 1000 && b->getLocation().y >= -10 && b->getLocation().y <= 1200) {
            new_bullets.push_back(b);
        }
    }
    bullet = new_bullets;

    new_bullets.clear();
    for (std::shared_ptr<Bullet> b : player_bullet) {
        b->move();
        if (b->getLocation().y >= 0)
            new_bullets.push_back(b);
    }
    player_bullet = new_bullets;
}

void World::spawnBullets() {
    for (std::shared_ptr<Spawner> s : spawner) {
        for (std::shared_ptr<Bullet> b : s->getBullets(frame)) {
            registerBullet(b);
        }
    }
}

void World::checkCollisions() {
    for (std::shared_ptr<Bullet> b : bullet) {
        if (intersect({b->getLocation(), b->getHitboxRadius()}, {player->getLocation(), player->getHitboxRadius()})) {
            parent.popState(1);
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
    window.clear();
    for (std::shared_ptr<Bullet> b : bullet) {
        b->draw(window);
    }
    for (std::shared_ptr<Bullet> b : player_bullet) {
        b->draw(window);
    }

    player->draw(window);
    window.display();
}
