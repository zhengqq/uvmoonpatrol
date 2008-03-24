#include "jetman.h"
#include <math.h>

typedef enum {
    WAITING=0,
    ACTIVATED,
    DONE
};

JetMan::JetMan(){
    printf("Default constructor does nothing!\n");
}

JetMan::JetMan(int startX){
    generateSprite("data\\flyingman.bmp", &jetSprite);
    jetX = startX;
    jetY = 50+rand()%5; // common starting y
    state = WAITING;
    gravity = 0.01; // gravity constant on the moon?
    velX = velY = 0.0;
    swoopCount = 0;
}

JetMan::~JetMan(){
    glDeleteTextures( 1, &jetSprite.texture );
}

void JetMan::update(int newScroll, JetFountain * myFountain, int carX, int carY){
    if ( state == WAITING ){
        if ( int(jetX) - carX < 300 ){
            state = ACTIVATED;
            myFountain->setActive(TRUE);
        }
    }
    if ( state == ACTIVATED ){
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
            myFountain->setActive(FALSE);
            velY = -2.0;
        }
        else{
            myFountain->setActive(TRUE);
        }
        myFountain->setPosition(int(jetX)+8,int(jetY)+8);
        if ( carX - int(jetX) > 200 ){
            state == DONE;
        }
    }
}

void JetMan::draw(){
    if ( state == ACTIVATED ){
        DrawSprite(jetSprite,int(jetX)-scrollX,int(jetY), FALSE);
    }
}
