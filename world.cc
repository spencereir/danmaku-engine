#include <vector>
#include <cmath>
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
        { {sf::Keyboard::A}, {}, std::make_shared<Commands::Player::MoveLeft>(*this, *player, player_vel)},
        { {sf::Keyboard::D}, {}, std::make_shared<Commands::Player::MoveRight>(*this, *player, player_vel)},
        { {sf::Keyboard::W}, {}, std::make_shared<Commands::Player::MoveUp>(*this, *player, player_vel)},
        { {sf::Keyboard::S}, {}, std::make_shared<Commands::Player::MoveDown>(*this, *player, player_vel)},
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
    view.reset({100, 900, (float)parent.getOptions().SCREEN_WIDTH, (float)parent.getOptions().SCREEN_HEIGHT});
    window.setView(view);
    std::shared_ptr<Spawner> s = std::make_shared<Spawners::BoWaP>(5, 3, 0.05, 5);
    s->setLocation({300,200});
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

int World::getFrame() {
    return parent.getClock().getTicker();
    //return round(parent.getClock().getElapsedTime().asSeconds() * parent.getOptions().FRAME_LIMIT);
}

void World::moveBullets(double velocity_factor) {
    for (std::shared_ptr<Bullet> b : bullet) {
        b->move(velocity_factor);
    }

    for (std::shared_ptr<Bullet> b : player_bullet) {
        b->move(velocity_factor);
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
        for (std::shared_ptr<Bullet> b : s->getBullets(getFrame())) {
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

void World::update() {
    double velocity_factor = (parent.getOptions().FRAME_SYNC ? parent.getClock().lap().asSeconds() * parent.getOptions().REF_FRAME : 1.0);
    player->move(velocity_factor);
    player->getVelocity().x = 0;
    player->getVelocity().y = 0;
    view.setCenter(player->getLocation().x, player->getLocation().y);
    window.setView(view);
    parent.getClock().tick();
    moveBullets(velocity_factor);
    spawnBullets();
    checkCollisions();
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
