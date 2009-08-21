#pragma once

#include <vector>
#include "base.h"
#include "gfx.h"
#include "jetfountain.h"

class JetFountain;

class JetMan : public Actor
{
public:
    JetMan(int, SpriteManager* );
    virtual ~JetMan();
    virtual int update(Level*,int);
    virtual int collision();
    virtual void draw();
    int getX(){return int(jetX);}
    int getY(){return int(jetY);}
    int width(){return jetSprite->width;}
    int height(){return jetSprite->height;}
private:
    unsigned int jetState;
    int swoopCount;
    Sprite * jetSprite;
    SpriteManager * sManager;
    int scrollX;
    double velX,velY,gravity,jetX,jetY;
};
