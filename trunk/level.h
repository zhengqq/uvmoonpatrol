#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "base.h"
#include "gfx.h"

class Level
{
public:
    Level();
    ~Level();
    void update();
    void draw();
private:
    Sprite tiles[4]; // 4 so far
};

#endif // __LEVEL_H__
