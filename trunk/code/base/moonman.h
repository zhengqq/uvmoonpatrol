#pragma once

#include "base.h"
#include "gfx.h"
#include "level.h"
#include "spriteManager.h"

class Level; // both level & moonman include each other.

class MoonMan {
public:
    MoonMan();
    MoonMan(int, SpriteManager*);
    ~MoonMan();
    void update(int,Level*);
    void draw();
    int getX(){return manX;}
    int getY(){return manY;}
    int width(){return manSpriteA->width;}
    int height(){return manSpriteA->height;}
private:
    unsigned int manState;
    unsigned int currentFrame;
    int manX,manY,speed;
    int scrollX;
    BOOL facingLeft;
    BOOL spriteA; // which sprite are we on?
    Sprite * manSpriteA;
    Sprite * manSpriteB;
    SpriteManager * sManager;
};

