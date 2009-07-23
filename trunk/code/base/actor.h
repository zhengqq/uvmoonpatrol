// Actor Class
/*
 *  The actor serves the purpose of being the parent of all objects on the screen.
 *  This way you can think of the screen as a "Stage" where actors are places, and
 *  all actors require certain things. This also makes having pools of actors with
 *  different inheritance much easier because you can simply declare a pool of inherited
 *  actors.
 */

#pragma once

#include "spriteManager.h" // do not touch! this is used for class declarations for children
#include "level.h"

#define ACTOR_IDLE          0x00
#define ACTOR_REMOVE        0x01
#define ACTOR_SETACTIVE     0x02

enum ActorType
{
    Collidable = 0,
    SlowDown,
    Destroyable,
    Projectile,
    Player
};

class Level;

class Actor{
 public:
    virtual int update(Level * lvl, int worldOffset) = 0; // physics updates?
    virtual int collision() = 0; // what happens during a collision?
    virtual void draw() = 0;
    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual int width() = 0;
    virtual int height() = 0;
    void setCollide(int collide){ collideWith = collide; }
    unsigned int collideType;
    unsigned int collideWith;
 private:
 };
