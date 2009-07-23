#include "bus.h"

enum{
    WAITING = 0,
    ACTIVATED
};

Bus::Bus()
{
    fprintf(stdout, "Cannot create an empty bus..");
}

Bus::Bus(int newX, SpriteManager * newManager)
{
    busX = newX;
    busY = 185;
    sManager = newManager;
    crashed = FALSE;
    velX = 2;
    state = WAITING;

    busSprite[0] = sManager->newSprite("data\\bus1_1.bmp");
    busSprite[1] = sManager->newSprite("data\\bus1_2.bmp");
    currentFrame = 0;
}

Bus::~Bus(){
    for(int i = 0; i < 2; i++)
        sManager->removeSprite(busSprite[i]);
}

void Bus::update(int inScroll, int carX)
{
    if ( state == WAITING ){
        if ( int(busX) - carX < 300 ){
            state = ACTIVATED;
        }
    }
    else if ( state == ACTIVATED ){
        busX += velX;
        scrollX = inScroll;
    }
}

void Bus::draw()
{
    DrawSprite(*busSprite[(currentFrame/10)], busX-scrollX, busY, true);
    currentFrame=(++currentFrame)%20;
}
