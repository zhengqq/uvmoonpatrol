#include "boulder.h"

typedef enum {
    ACTIVE=0,
    EXPLODING
};

Boulder::Boulder(){
    printf("Nothing to be done for default constructor of boulder.cpp\n");
}

Boulder::Boulder(int newX, int type){
    boulderX = newX;
    if ( type == SMALL_BOULDER ) boulderY = 188;
    else if ( type == LARGE_BOULDER ) boulderY = 172;
    levelX = 0;
    if ( type == LARGE_BOULDER ){
        if(!generateSprite("data\\boulder1.bmp",&boulderSprite)) printf("Could not load boulder1.bmp\n");
        generateSprite("data\\explosion2_1.bmp",&explodeSprites[0]);
        generateSprite("data\\explosion2_2.bmp",&explodeSprites[1]);
        generateSprite("data\\explosion2_3.bmp",&explodeSprites[2]);
    }
    else if ( type == SMALL_BOULDER ){
        if(!generateSprite("data\\boulder2.bmp",&boulderSprite)) printf("Could not load boulder2.bmp\n");
        generateSprite("data\\explosion3_1.bmp",&explodeSprites[0]);
        generateSprite("data\\explosion3_2.bmp",&explodeSprites[1]);
        generateSprite("data\\explosion3_3.bmp",&explodeSprites[2]);
    }
    life = 14; // how long the explosion will last!
    currentState = ACTIVE;
}

Boulder::~Boulder(){
    glDeleteTextures( 1, &boulderSprite.texture );
    for ( int i = 0; i < 3; i++)
        glDeleteTextures( 1, &explodeSprites[i].texture );
}

void Boulder::update(int scrollX){
    levelX = scrollX;
    if ( currentState == EXPLODING ){
        life--;
    }
}

void Boulder::draw(){
    if ( currentState == ACTIVE ){
        DrawSprite(boulderSprite, boulderX-levelX, boulderY, FALSE);
    }
    else {
        DrawSprite(explodeSprites[2-(life/5)], boulderX-levelX, boulderY, FALSE);
    }
}

BOOL Boulder::isActive(){
    if ( currentState == ACTIVE ) return TRUE;
    else return FALSE;
}

BOOL Boulder::isDead(){
    if ( life <= 0 ) return TRUE;
    else return FALSE;
}

void Boulder::setExplode(){
    currentState = EXPLODING;
}

int Boulder::width(){
    return boulderSprite.width;
}

int Boulder::height(){
    // Do something fancy for our smaller boulders?
    return boulderSprite.height;
}
