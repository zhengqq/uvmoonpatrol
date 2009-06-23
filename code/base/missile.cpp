#include "missile.h"

Missile::Missile(){
    printf("Default constructor for missile does nothing!\n");
}

Missile::Missile(int startX, int startY, SpriteManager * newManager){
    sManager = newManager;
    misX = startX;
    misY = startY;
    missileSprite = sManager->newSprite("data\\missile.bmp");
}

Missile::~Missile()
{
    sManager->removeSprite(missileSprite);
}

void Missile::update(){
    if ( misY > 0 ){
        misY -= 6; // fly upward!
    }
}

void Missile::draw(){
    DrawSprite(*missileSprite, misX,misY,FALSE);
}
