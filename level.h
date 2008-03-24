#pragma once

#include "base.h"
#include "gfx.h"
#include "moonman.h"
#include "jetman.h"
#include "jetfountain.h"
#include "boulder.h"

class MoonMan;

class Level
{
public:
    Level();
    ~Level();
    void update(int);
    void draw();
    BOOL isGround(int,int);
    BOOL isPit(int);
    void generateMoonMen(MoonMan ** manArray);
    void generateBoulders(Boulder ** boulderArray);
    void generateJetMen(JetMan **, JetFountain **);
private:
    Sprite tiles[6]; // 6 so far
    Sprite spaceBG; // space background
    Sprite farBG; // farthest background
    Sprite closeBG; // closest background
    int levelX;
};
