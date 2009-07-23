#pragma once

//#include <vector>
#include "base.h"
#include "actorpool.h"

/*
#include "moonman.h"
#include "jetman.h"
#include "jetfountain.h"
#include "boulder.h"
#include "bus.h"
#include "damagedman.h"

class MoonMan;
class DamagedMan;
class JetMan;
class Bus;
class Boulder;
*/

class ActorPool;
class SpriteManager;

class Level
{
public:
    Level(SpriteManager *);
    ~Level();
    void update(int, ActorPool*, int);
    void draw();
    BOOL isGround(int,int);
    BOOL isPit(int);
    /*
    void generateMoonMen(std::vector<MoonMan*> * manArray);
    void generateBoulders(std::vector<Boulder*> *boulderArray);
    void generateJetMen(std::vector<JetMan*> *, std::vector<JetFountain*> *);
    void generateBuses(std::vector<Bus*> *);
    */
private:
    Sprite * tiles[7]; // 7 so far
    Sprite * spaceBG; // space background
    Sprite * farBG; // farthest background
    Sprite * closeBG; // closest background
    SpriteManager * sManager;
    int levelX;
};
