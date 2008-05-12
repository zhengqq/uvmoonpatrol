#include "missile.h"

Missile::Missile(){
    printf("Default constructor for missile does nothing!\n");
}

Missile::Missile(int startX, int startY){
    misX = startX;
    misY = startY;
    generateSprite("data\\missile.bmp",&missileSprite);
}

Missile::~Missile()
{
    glDeleteTextures( 1, &missileSprite.texture );
}

void Missile::update(){
    if ( misY > 0 ){
        misY -= 6; // fly upward!
    }
}

void Missile::draw(){
    DrawSprite(missileSprite, misX,misY,FALSE);
}
