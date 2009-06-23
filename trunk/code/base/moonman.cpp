#include "moonman.h"

typedef enum {
    RUNNING = 0,
    WALKING,
    DEAD
};

MoonMan::MoonMan(){
    printf("Default constructor does nothing for moon man!\n");
}

MoonMan::MoonMan(int startX, SpriteManager * newManager){
    sManager = newManager;
    manState = RUNNING;
    currentFrame = 0;
    facingLeft = FALSE;
    spriteA = TRUE;
    manSpriteA = sManager->newSprite("data\\running1_1.bmp");
    manSpriteB = sManager->newSprite("data\\running1_2.bmp");
    manX = startX;
    manY = 100; // will snap to the level
    speed = 2;
}

MoonMan::~MoonMan(){
    sManager->removeSprite(manSpriteA);
    sManager->removeSprite(manSpriteB);
}

void MoonMan::update(int newScroll, Level * currentLevel){
    scrollX = newScroll;
    if ( manState == RUNNING )
    {
        currentFrame ++;
        if ( currentFrame > 2 ){
            spriteA = !spriteA;
            currentFrame = 0;
        }
        // DEBUG!!
        if ( manX - scrollX < 300 ){
            if ( !currentLevel->isPit(manX+8+speed) ){
                if ( manX < 164 * 32 ){
                    manX += speed;
                }
                manY = 175; // some number that is always above ground // 196 is the min
                while( !currentLevel->isGround(manX+8,manY+19)){
                        manY++;
                }
            }
        }
    }
    else if ( manState == DEAD)
    {
        // We're dead, change sprite to dead sprite
    }
}

void MoonMan::draw(){
    if ( spriteA == TRUE ){
        DrawSprite(*manSpriteA, manX-scrollX, manY, facingLeft);
    }
    else{
        DrawSprite(*manSpriteB, manX-scrollX, manY, facingLeft);
    }
}

