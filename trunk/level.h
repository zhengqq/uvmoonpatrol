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
private:
    Sprite tiles[4]; // 4 so far
    Sprite spaceBG; // space background
    Sprite farBG; // farthest background
    Sprite closeBG; // closest background
    int levelX;
    int spaceX; // 0-480  SLOW
    int farX;   // 0-480  moderately slow
    int closeX; // 0-960  somewhat slow
};

#endif // __LEVEL_H__
