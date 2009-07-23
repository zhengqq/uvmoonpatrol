#pragma once

#include "base.h"
#include "gfx.h"
#include "level.h"

class MoonMan : public Actor
{
public:
    MoonMan(int, SpriteManager*);
    ~MoonMan();
    virtual int update(Level*,int);
    virtual int collision();
    virtual void draw();
    virtual int getX(){return manX;}
    virtual int getY(){return manY;}
    virtual int width(){return manSpriteA->width;}
    virtual int height(){return manSpriteA->height;}
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

