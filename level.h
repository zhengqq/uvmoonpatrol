#pragma once

#include "base.h"
#include "gfx.h"
#include "moonman.h"

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
private:
    Sprite tiles[6]; // 6 so far
    Sprite spaceBG; // space background
    Sprite farBG; // farthest background
    Sprite closeBG; // closest background
    int levelX;
};
