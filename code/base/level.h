#pragma once

#include <vector>
#include "base.h"
#include "gfx.h"
#include "moonman.h"
#include "jetman.h"
#include "jetfountain.h"
#include "boulder.h"
#include "bus.h"
#include "damagedman.h"

class MoonMan;
class DamagedMan;
class Bus;

class Level
{
public:
    Level(SpriteManager *);
    ~Level();
    void update(int);
    void draw();
    BOOL isGround(int,int);
    BOOL isPit(int);
    void generateMoonMen(std::vector<MoonMan*> * manArray);
    void generateBoulders(std::vector<Boulder*> *boulderArray);
    void generateJetMen(std::vector<JetMan*> *, std::vector<JetFountain*> *);
    void generateBuses(std::vector<Bus*> *);
private:
    Sprite * tiles[7]; // 7 so far
    Sprite * spaceBG; // space background
    Sprite * farBG; // farthest background
    Sprite * closeBG; // closest background
    SpriteManager * sManager;
    int levelX;
};
