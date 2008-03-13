#include "car.h"

Car::Car()
{
    // Get some private variables declared
    screenX = currentFrame = 0;
    carX = 20;
    carY = 175;
    airBorne = movingLeft = movingRight = FALSE;
    speed = 5;
    wheelA = TRUE;
    if (!generateSprite("data\\car.bmp",&carSprite) ){
        printf("Error, could not load car.bmp!\n");
    }
    if (!generateSprite("data\\wheel1_1.bmp",&wheelSpriteA[0]) ){
        printf("Error, could not load wheel1_1.bmp!\n");
    }
    if (!generateSprite("data\\wheel2_1.bmp",&wheelSpriteA[1]) ){
        printf("Error, could not load wheel2_1.bmp!\n");
    }
    if (!generateSprite("data\\wheel3_1.bmp",&wheelSpriteA[2]) ){
        printf("Error, could not load wheel3_1.bmp!\n");
    }
    if (!generateSprite("data\\wheel1_2.bmp",&wheelSpriteB[0]) ){
        printf("Error, could not load wheel1_1.bmp!\n");
    }
    if (!generateSprite("data\\wheel2_2.bmp",&wheelSpriteB[1]) ){
        printf("Error, could not load wheel2_1.bmp!\n");
    }
    if (!generateSprite("data\\wheel3_2.bmp",&wheelSpriteB[2]) ){
        printf("Error, could not load wheel3_1.bmp!\n");
    }

} // Constructor

Car::~Car()
{
    glDeleteTextures( 1, &carSprite.texture );
    for(int i = 0; i < 3; i++)
    {
        glDeleteTextures( 1, &wheelSpriteA[i].texture );
        glDeleteTextures( 1, &wheelSpriteB[i].texture );
    }
} // Deconstructor

void Car::update()
{
    currentFrame ++;
    if ( currentFrame > 1 )
    {
        wheelA = !wheelA;
        currentFrame = 0;
    }
    carY = 175;
    screenX += int(carX/50)+1; // ?
} // give this the level terrain?

void Car::draw()
{
    DrawSprite(carSprite, carX, carY, FALSE);
    if ( wheelA == TRUE ){
        DrawSprite(wheelSpriteA[0], carX-3, carY+16, FALSE);
        DrawSprite(wheelSpriteA[1], carX+8, carY+17, FALSE);
        DrawSprite(wheelSpriteA[2], carX+19, carY+16, FALSE);
    }
    else{
        DrawSprite(wheelSpriteB[0], carX-3, carY+16, FALSE);
        DrawSprite(wheelSpriteB[1], carX+8, carY+17, FALSE);
        DrawSprite(wheelSpriteB[2], carX+19, carY+16, FALSE);
    }
}

void Car::fire()
{
}

bool Car::moveLeft()
{
    if ( (carX-speed) > 15 ){
        carX-= speed;
    }
    else{
        carX = 15;
    }
}

bool Car::moveRight()
{
    if ( ((carX+speed)+carSprite.width) < 150 ){
        carX+= speed;
    }
    else{
        carX = (150-carSprite.width);
    }
}

void Car::stopMove()
{
    movingLeft = movingRight = FALSE;
}

void Car::jump()
{
}
