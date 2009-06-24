#include "damagedman.h"

typedef enum {
    FLYING = 0,
    DEAD
};

DamagedMan::DamagedMan(int startX, SpriteManager * newManager, int startAngle){
    sManager = newManager;
    manState = FLYING;
    damageSprite = sManager->newSprite("data\\damagedman.bmp");
    manX = startX;
    manY = 175; // will snap to the level
    speed = rand()%20/10 + 5;
    if ( startAngle > 90 ){
        facingLeft = TRUE;
    }
    else{
        facingLeft = FALSE;
    }
}

DamagedMan::~DamagedMan(){
    sManager->removeSprite(damageSprite);
}

void DamagedMan::update(int newScroll, Level * currentLevel){
    scrollX = newScroll;
    if ( manState == FLYING )
    {
        // DEBUG!!
        if ( manX - scrollX < 300 ){
            // will eventually move around and be awesome
            manY = 175;
        }
        else{
            manState = DEAD;
        }
    }
    else if ( manState == DEAD)
    {
        // We're dead, change sprite to dead sprite
    }
}

void DamagedMan::draw(){
    DrawSprite(*damageSprite, manX-scrollX, manY, false);
}

