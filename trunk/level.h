#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "base.h"
#include "gfx.h"

class Level
{
public:
    Level();
    ~Level();
    void update(int);
    void draw();
    BOOL isGround(int,int);
private:
    Sprite tiles[4]; // 4 so far
    Sprite spaceBG; // space background
    Sprite farBG; // farthest background
    Sprite closeBG; // closest background
    int levelX;
};

#endif // __LEVEL_H__
