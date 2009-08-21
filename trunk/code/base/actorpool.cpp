#include "actorpool.h"

ActorPool::ActorPool()
{
    // Don't need anything right now
}

ActorPool::~ActorPool()
{
    // Clean the pool
    cleanPool();
}

int ActorPool::createGroup()
{
    std::vector<Actor*> newVector;
    pool.push_back(newVector);
    return pool.size()-1;
}

void ActorPool::addActor(Actor* actor, int idx)
{
    pool[idx].push_back(actor);
}

std::vector<Actor*> * ActorPool::getPool(int i)
{
    return &pool[i];
}

void ActorPool::cleanPool()
{
    // Clear all the actors inside each pool
    for(unsigned int i = 0; i < pool.size(); i++)
    {
        for(unsigned int j = 0; j < pool[i].size(); j++)
        {
            Actor* actor = pool[i][j];
            delete actor;
        }
        pool[i].clear();
    }
    pool.clear();
}

void ActorPool::updatePhysics(Level * level, int worldOffset)
{
    // Clear our collision list
    collisionPool.clear();
    unsigned int ret = 0;
    for(unsigned int i = 0; i < pool.size(); i++)
    {
        for(unsigned int j = 0; j < pool[i].size(); j++)
        {
            Actor* actor = pool[i][j];
            ret = actor->update(level, worldOffset);
            if( ret == ACTOR_REMOVE )
            {
                pool[i].erase(pool[i].begin()+j,pool[i].begin()+j+1);
            }
        }
    }
}

void ActorPool::checkCollision(int A, int B)
{
    std::vector<Actor*> poolA = pool[A];
    std::vector<Actor*> poolB = pool[B];
    for(unsigned int i = 0; i < poolA.size(); i++)
    {
        // check collision against everything in poolB
        for(unsigned int j = 0; j < poolB.size(); j++)
        {
            if ( rectCollision(poolA[i]->getX(), poolA[i]->getY(), poolA[i]->width(), poolA[i]->height(),
                        poolB[j]->getX(), poolB[j]->getY(), poolB[j]->width(), poolB[j]->height()) ){ // this WILL push two collisions into the collision pool, no smart checks yet
                collisionPool.push_back(poolA[i]);
                poolA[i]->collideWith = poolB[j]->collideType;
                collisionPool.push_back(poolB[j]);
                poolB[j]->collideWith = poolA[i]->collideType;
            }
        }
    }
}

void ActorPool::updateCollisions()
{
    for(unsigned int i = 0; i < collisionPool.size(); i++)
    {
        collisionPool[i]->collision(); // do a collision!
    }
}

void ActorPool::drawPool()
{
    for(unsigned int i = 0; i < pool.size(); i++)
    {
        for(unsigned int j = 0; j < pool[i].size(); j++)
        {
            pool[i][j]->draw();
        }
    }
}
