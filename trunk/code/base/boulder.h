#ifndef __BOULDER_H__
#define __BOULDER_H__

#include "base.h"
#include "gfx.h"

typedef enum {
    SMALL_BOULDER=0,
    LARGE_BOULDER,  // left boulder, largest boulder
    RIGHT_BOULDER   // right boulder, used for doulbing up
};

class Boulder
{
public:
    Boulder();
    Boulder(int,int, SpriteManager*);
    virtual ~Boulder();
    virtual int update(Level*,int);
    virtual int collision(){ return 0; }
    virtual void draw();
    int getX(){return boulderX;}
    int getY(){return boulderY;}
    int width();
    int height();
    void setExplode();
    BOOL isActive();
    BOOL isDead();
private:
    SpriteManager * sManager;
    Sprite * boulderSprite;
    Sprite * explodeSprites[3];
    int levelX,boulderX,boulderY;
    int life, currentState;
};

#endif // __BOULDER_H__
