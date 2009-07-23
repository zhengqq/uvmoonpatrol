#ifndef __MISSILE_H__
#define __MISSILE_H__

#include "base.h"
#include "gfx.h"

class Missile
{
public:
    Missile();
    Missile(int,int, SpriteManager*);
    ~Missile();
    virtual int update();
    void draw();
    int getX(){ return misX; }
    int getY(){ return misY; }
    int width(){ return 1; }
    int height(){ return 4; }
private:
    int misX,misY;
    Sprite * missileSprite;
    SpriteManager * sManager;
};

#endif // __MISSILE_H__
