#include "world.h"
#include "resources.h"
#include "spawner.h"
#include "bullet.h"
#include "player.h"
#include "game.h"
#include "pause.h"
#include "hitbox.h"
#include <vector>

World::World(Game *g) : GameState{g}, player{new Player}  {
    player->setLocation({100,900});
    Spawner *s = new Spawners::BoWaP{1, 144, 0, 1};
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

void World::registerPlayer(Player *p) {
    player = p;
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

std::vector<Bullet*> World::getBullets() {
    auto x = bullet;
    for (auto y : player_bullet) x.push_back(y);
    return x;
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

void World::handleInput(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            parent->pushState(new Pause{parent});
        } else if (event.key.code == sf::Keyboard::LShift) {
            player_vel = 2;
        }
    } else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::LShift) {
            player_vel = 5;
        }
    }
}

void World::update() {
    frame++;
    player_vec = {0,0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        player_vec.y = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        player_vec.y = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player_vec.x = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player_vec.x = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        spawnPlayerBullets();
    }
    player->move(player_vec * player_vel);
    moveBullets();
    spawnBullets();
    checkCollisions();
}

void World::draw() {
    window->clear();
    for (Bullet *b : getBullets()) {
        b->draw(window);
    }

    player->draw(window);
    window->display();
}
