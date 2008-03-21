#include "moonman.h"

typedef enum {
    RUNNING = 0,
    WALKING,
    DEAD
};

MoonMan::MoonMan(){
    printf("Default constructor does nothing for moon man!\n");
}

MoonMan::MoonMan(int startX){
    manState = RUNNING;
    currentFrame = 0;
    facingLeft = FALSE;
    spriteA = TRUE;
    if ( !generateSprite("data\\running1_1.bmp", &manSpriteA))
    {
        printf("Could not load moon man running1_1.bmp\n");
    }
    if ( !generateSprite("data\\running1_2.bmp", &manSpriteB))
    {
        printf("Could not load moon man running1_1.bmp\n");
    }
    manX = startX;
    manY = 100; // will snap to the level
    speed = 2;
}

MoonMan::~MoonMan(){
    glDeleteTextures( 1, &manSpriteA.texture );
    glDeleteTextures( 1, &manSpriteB.texture );
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
        /*
        if ( facingLeft ){
            if ( rand()%50 == 3 ){
                facingLeft = FALSE;
            }
            else{
                manX -= speed;
            }
        }
        else {
            if ( rand()%50 == 13 ){
                facingLeft = TRUE;
            }
            else{
                manX += speed;
            }
        }*/
        // DEBUG!!
        if ( manX < 164 * 32 ){
            manX += speed;
        }
        manY = 175; // some number that is always above ground // 196 is the min
        while( !currentLevel->isGround(manX+8,manY+19)){
                manY++;
        }
    }
    else if ( manState == DEAD)
    {
        // We're dead, change sprite to dead sprite
    }
}

void MoonMan::draw(){
    if ( spriteA == TRUE ){
        DrawSprite(manSpriteA, manX-scrollX, manY, facingLeft);
    }
    else{
        DrawSprite(manSpriteB, manX-scrollX, manY, facingLeft);
    }
}

void MoonMan::kill() {
    manState = DEAD;
}
