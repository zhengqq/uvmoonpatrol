#include "moonman.h"

typedef enum {
    RUNNING = 0,
    WALKING,
    DEAD
};

MoonMan::MoonMan(int startX, SpriteManager * newManager){
    sManager = newManager;
    manState = RUNNING;
    currentFrame = 0;
    facingLeft = FALSE;
    spriteA = TRUE;
    manSpriteA = sManager->newSprite("data\\running1_1.bmp");
    manSpriteB = sManager->newSprite("data\\running1_2.bmp");
    manX = startX;
    manY = 175; // will snap to the level
    speed = 2;
    collideType = SlowDown;
}

MoonMan::~MoonMan(){
    sManager->removeSprite(manSpriteA);
    sManager->removeSprite(manSpriteB);
}

int MoonMan::collision()
{
    // Do different effects for each type of impact?
    if ( collideWith == Player ){
        manState = DEAD;
    }
}

int MoonMan::update(Level * currentLevel, int newScroll){
    scrollX = newScroll;
    if ( manState == RUNNING )
    {
        currentFrame ++;
        if ( currentFrame > 2 ){
            spriteA = !spriteA;
            currentFrame = 0;
        }
        if ( !currentLevel->isPit(manX+8+speed) ){
            if ( manX < 164 * 32 ){
                manX += speed;
            }
            manY = 176; // some number that is always above ground // 196 is the min
            while( !currentLevel->isGround(manX+8,manY+19)){
                    manY++;
            }
        }
        if ( scrollX - manX > 32 ){ // off the screen
            manState = DEAD;
        }
    }
    else if ( manState == DEAD)
    {
        // We're dead, change sprite to dead sprite
        return ACTOR_REMOVE;
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

