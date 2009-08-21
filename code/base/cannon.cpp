#include "cannon.h"

Cannon::Cannon(){
    printf("Default constructor for cannon does nothing!\n");
}

Cannon::Cannon(int startX, int startY, SpriteManager * newManager){
    canX = startCanX = startX;
    canY = startY;
    levelX = 0;
    life = 18;
    sManager = newManager;
    cannonSprite = sManager->newSprite("data\\cannon.png");
    explosionSprite[0] = sManager->newSprite("data\\explosion1_1.png");
    explosionSprite[1] = sManager->newSprite("data\\explosion1_2.png");
    explosionSprite[2] = sManager->newSprite("data\\explosion1_3.png");
}

Cannon::~Cannon(){
    sManager->removeSprite(cannonSprite);
    for(int i = 0; i < 3; i++)
        sManager->removeSprite(explosionSprite[i]);
}

void Cannon::update(int scrollX){
    levelX = scrollX;
    if ( (canX-startCanX) < 150 ){
        canX+=10;
    }
    else{
        life--;
    }
}

void Cannon::draw(){
    if ( life == 18 ){
        DrawSprite(*cannonSprite, canX-levelX,canY,FALSE);
    }
    else if ( life > 12 ){
        DrawSprite(*explosionSprite[0], canX-levelX,canY-4,FALSE);
    }
    else if ( life > 6 ){
        DrawSprite(*explosionSprite[1], canX-levelX,canY-4,FALSE);
    }
    else{
        DrawSprite(*explosionSprite[2], canX-levelX,canY-4,FALSE);
    }
}

int Cannon::width(){
    if ( life == 18 ){
        return 8;
    }
    else {
        return 16;
    }
}

int Cannon::height(){
    if ( life == 18 ){
        return 8;
    }
    else {
        return 16;
    }
}
