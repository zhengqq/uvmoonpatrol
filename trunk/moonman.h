#ifndef __MOONMAN_H__
#define __MOONMAN_H__

#include "base.h"
#include "gfx.h"

class MoonMan {
public:
    MoonMan();
    ~MoonMan();
    void update();
    void draw();
    int getX(){return manX;}
    int getY(){return manY;}
    int width(){return manSpriteA.width;}
    int height(){return manSpriteA.height;}
    void kill();
private:
    unsigned int manState;
    unsigned int currentFrame;
    int manX,manY,speed;
    BOOL facingLeft;
    BOOL spriteA; // which sprite are we on?
    Sprite manSpriteA;
    Sprite manSpriteB;
};

#endif // __MOONMAN_H__
