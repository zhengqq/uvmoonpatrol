#pragma once

#include <vector>
#include "actor.h"

class Actor;
class Level;

class ActorPool{
public:
    ActorPool();
    ~ActorPool();
    int createGroup();
    void cleanPool();
    void addActor(Actor*, int);
    std::vector<Actor*> * getPool(int);
    void updatePhysics(Level * lvl, int worldOffset);  // update everything in our pool!
    void checkCollision(int, int); // check collisions between two groups
    void updateCollisions(); // update anyone who collided
    void drawPool();    // draw all the contents of the pool!
private:
    std::vector< std::vector<Actor*> > pool; // List of actor pools
    std::vector<Actor*> collisionPool;
};
