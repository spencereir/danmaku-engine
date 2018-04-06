#ifndef __WORLD_H_
#define __WORLD_H_

#include <vector>
#include <memory>
#include "game.h"
#include "background.h"
#include "clock.h"

class Bullet;
class Spawner;
class Player;

class World : public GameState {
    std::unique_ptr<Player> player;
    std::vector< std::shared_ptr<Bullet> > bullet;
    std::vector< std::shared_ptr<Bullet> > player_bullet;
    std::vector< std::shared_ptr<Spawner> > spawner;
    double frame = 0;
    double velocity_scaling_factor;
    Background b;

    void moveBullets();
    void spawnBullets();
    void spawnPlayerBullets();
    void checkCollisions();
public:
    World(Game&);
    void registerBullet(std::shared_ptr<Bullet>);
    void registerPlayerBullet(std::shared_ptr<Bullet>);
    void registerSpawner(std::shared_ptr<Spawner>);

    void update() override;
    void draw() override;

    int getFrame() { return frame; }
    double getVelocityScalingFactor() { return velocity_scaling_factor; }
};


#endif
