#include <vector>
#include <algorithm>
#include "world.h"
#include "resources.h"
#include "spawner.h"
#include "bullet.h"
#include "player.h"
#include "game.h"
#include "pause.h"
#include "hitbox.h"
#include "input.h"

World::World(Game &g) : GameState{g}, player{std::make_unique<Player>()}, b{"bg.png", g.getOptions()} {
    double player_vel = 5.0;
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

    parent.getClock().restart();

    player->setLocation({100,900});
    std::shared_ptr<Spawner> s = std::make_shared<Spawners::BoWaP>(1, 6, 0.05, 3);
//    std::shared_ptr<Spawner> s = std::make_shared<Spawners::Spread>(PI/3.0);
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
    for (std::shared_ptr<Bullet> b : bullet) {
        b->move(frame);
    }

    for (std::shared_ptr<Bullet> b : player_bullet) {
        b->move(frame);
    }

    auto is_oob = [](std::shared_ptr<Bullet> b) -> bool {
        Vec2 v = b->getLocation();
        return (v.x < -10 || v.x > 1000 || v.y < -10 || v.y > 1200);
    };
    bullet.erase(std::remove_if(bullet.begin(), bullet.end(), is_oob), bullet.end());
    player_bullet.erase(std::remove_if(player_bullet.begin(), player_bullet.end(), is_oob), player_bullet.end());
}

void World::spawnBullets() {
    for (std::shared_ptr<Spawner> s : spawner) {
        for (std::shared_ptr<Bullet> b : s->getBullets(frame)) {
            registerBullet(b);
        }
    }

    auto is_dead = [this](std::shared_ptr<Spawner> s) -> bool {
        return s->isFinished();
    };
    spawner.erase(std::remove_if(spawner.begin(), spawner.end(), is_dead), spawner.end());
}

void World::checkCollisions() {
    for (std::shared_ptr<Bullet> b : bullet) {
        if (intersect({b->getLocation(), b->getHitboxRadius()}, {player->getLocation(), player->getHitboxRadius()})) {
            parent.popState(1);
            return;
        }
    }
}

#include <iostream>
void World::update() {
    velocity_scaling_factor = parent.getClock().lap().asMicroseconds() / 16666.666;
    std::cout << velocity_scaling_factor << std::endl;

    frame = parent.getClock().getElapsedTime().asMicroseconds() / 16666.666;
    moveBullets();
    spawnBullets();
    checkCollisions();
    b.move(velocity_scaling_factor);
}

void World::draw() {
    window.clear();
    b.draw(window);
    for (std::shared_ptr<Bullet> b : bullet) {
        b->draw(window);
    }
    for (std::shared_ptr<Bullet> b : player_bullet) {
        b->draw(window);
    }

    player->draw(window);
    window.display();
}
