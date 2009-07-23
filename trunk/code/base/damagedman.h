#pragma once

#include "base.h"
#include "gfx.h"
#include "level.h"

class Level; // both level & moonman include each other.

class DamagedMan{
public:
    DamagedMan();
    DamagedMan(int, SpriteManager*,int);
    ~DamagedMan();
    void update(int,Level*);
    void draw();
    int getX(){return manX;}
    int getY(){return manY;}
    int width(){return damageSprite->width;}
    int height(){return damageSprite->height;}
private:
    int manState;
    int manX,manY;
    double speed;
    int scrollX;
    BOOL facingLeft;
    Sprite * damageSprite;
    SpriteManager * sManager;
};

