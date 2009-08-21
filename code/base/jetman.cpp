#include "jetman.h"
#include <math.h>

JetMan::JetMan(int startX, SpriteManager * newManager){
    sManager = newManager;
    jetSprite = sManager->newSprite("data\\flyingman.png");
    jetX = startX;
    jetY = 50+rand()%5; // common starting y
    gravity = 0.01; // gravity constant on the moon?
    velX = velY = 0.0;
    swoopCount = 0;
}

JetMan::~JetMan(){
    sManager->removeSprite(jetSprite);
}

int JetMan::update(Level * currentLevel, int newScroll){
/*    JetFountain * curFountain = *(myFountain);
    if ( state == WAITING ){
        if ( int(jetX) - carX < 300 ){
            state = ACTIVATED;
            curFountain->setActive(TRUE);
        }
    }
    else if ( state == ACTIVATED ){
        scrollX = newScroll;
        if ( swoopCount < 2 )
            velX = ((carX - jetX)/10)+5;
        else {
            velX = -1.0; // some slow number
        }
        if ( jetY >= 140 ){
            swoopCount++; // increment our swoop count!
            velY = 1.0; // boost upwards!
        }
        jetX += velX;
        velY -= gravity;
        jetY -= velY;
        if ( velY < -2.0 ){
            curFountain->setActive(FALSE);
            velY = -2.0;
        }
        else{
            curFountain->setActive(TRUE);
        }
        curFountain->setPosition(int(jetX)+8,int(jetY)+8);
        if ( carX - int(jetX) > 200 ){
            state == DONE;
        }
    }
    */

    if ( scrollX - jetX > 32 )
    {
        // We're dead, change sprite to dead sprite
        return ACTOR_REMOVE;
    }

    scrollX = newScroll;
    return ACTOR_IDLE;
}

int JetMan::collision(){
    // Do different effects for each type of impact?
    if ( collideWith == Player ){
        // kill?
    }
    return 0;
}

void JetMan::draw(){
    DrawSprite(*jetSprite,int(jetX)-scrollX,int(jetY), FALSE);
}
