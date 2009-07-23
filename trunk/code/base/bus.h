#pragma once

#include "base.h"
#include "gfx.h"

class Bus{
public:
    Bus();
    Bus(int, SpriteManager*);
    ~Bus();
    void update(int,int);
    void draw();
    int width(){return busSprite[0]->width;}
    int height(){return busSprite[0]->height;}
    int getX(){return int(busX);}
    int getY(){return busY;}
    BOOL isActive(){ return !crashed; }
    BOOL isDead(){ return crashed; }
    void setExplode(){ crashed = TRUE; }
private:
    Sprite * busSprite[2];
    SpriteManager * sManager;
    int scrollX, busY, state;
    int velX, busX;
    bool crashed;
    unsigned int currentFrame;
};
