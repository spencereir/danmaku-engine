#ifndef __WORLD_H_
#define __WORLD_H_

#include <vector>
#include "game.h"

class Bullet;
class Spawner;
class Player;

class World : public GameState {
    Player *player;
    std::vector<Bullet*> bullet;
    std::vector<Bullet*> player_bullet;
    std::vector<Spawner*> spawner;
    void moveBullets();
    void spawnBullets();
    void spawnPlayerBullets();
    void checkCollisions();
    int frame = 0;

    Vec2 player_vec;
    double player_vel;

public:
    World(Game*);
    ~World();
    void registerBullet(Bullet*);
    void registerPlayerBullet(Bullet*);
    void registerSpawner(Spawner*);

    void update() override;
    void draw() override;
};


#endif
