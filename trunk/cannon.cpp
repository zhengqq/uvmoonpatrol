#include "cannon.h"

Cannon::Cannon(){
    printf("Default constructor for cannon does nothing!\n");
}

Cannon::Cannon(int startX, int startY){
    canX = startCanX = startX;
    canY = startY;
    levelX = 0;
    life = 18;
    generateSprite("data\\cannon.bmp", &cannonSprite);
    generateSprite("data\\explosion1_1.bmp", &explosionSprite[0]);
    generateSprite("data\\explosion1_2.bmp", &explosionSprite[1]);
    generateSprite("data\\explosion1_3.bmp", &explosionSprite[2]);
}

Cannon::~Cannon(){
    glDeleteTextures( 1, &cannonSprite.texture );
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
        DrawSprite(cannonSprite, canX-levelX,canY,FALSE);
    }
    else if ( life > 12 ){
        DrawSprite(explosionSprite[0], canX-levelX,canY-4,FALSE);
    }
    else if ( life > 6 ){
        DrawSprite(explosionSprite[1], canX-levelX,canY-4,FALSE);
    }
    else{
        DrawSprite(explosionSprite[2], canX-levelX,canY-4,FALSE);
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
        return 4;
    }
    else {
        return 16;
    }
}
