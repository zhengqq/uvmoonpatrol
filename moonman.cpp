#include "moonman.h"

enum {
    RUNNING = 0,
    WALKING,
    DEAD
};

MoonMan::MoonMan(){
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
    manX = rand()%200 + 35;
    manY = 190;
    speed = 2;
}

MoonMan::~MoonMan(){
    glDeleteTextures( 1, &manSpriteA.texture );
    glDeleteTextures( 1, &manSpriteB.texture );
}

void MoonMan::update(){
    if ( manState == RUNNING )
    {
        currentFrame ++;
        if ( currentFrame > 2 ){
            spriteA = !spriteA;
            currentFrame = 0;
        }
        if ( facingLeft ){
            if ( manX - speed < 0 ){
                manX = 0;
                facingLeft = FALSE;
            }
            else{
                manX -= speed;
            }
        }
        else {
            if ( (manX + speed + manSpriteA.width) > SCREEN_WIDTH ){
                manX = SCREEN_WIDTH - manSpriteA.width;
                facingLeft = TRUE;
            }
            else{
                manX += speed;
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
        DrawSprite(manSpriteA, manX, manY, facingLeft);
    }
    else{
        DrawSprite(manSpriteB, manX, manY, facingLeft);
    }
}

void MoonMan::kill() {
    manState = DEAD;
}
