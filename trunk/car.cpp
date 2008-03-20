#include "car.h"

Car::Car()
{
    // Get some private variables declared
    screenX = currentFrame = 0;
    carX = 45;
    carY = 100;
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

void Car::update(Level * curLevel)
{
    currentFrame ++;
    if ( currentFrame > 1 )
    {
        wheelA = !wheelA;
        currentFrame = 0;
    }
    // Set our wheel sprites x values
    wheelX[0] = int(carX)-3;
    wheelX[1] = int(carX)+6;
    wheelX[2] = int(carX)+18;
    // do some y calculations!
    int lowestY = 0; // wheel 0 has the lowest y
    for(int i = 0; i < 3; i++)
    {
        wheelY[i]=int(carY);
        BOOL hitFloor=FALSE;
        while( !curLevel->isGround(wheelX[i]+screenX+3,wheelY[i]+16)){
            wheelY[i]++;
        }
        if ( wheelY[i] < wheelY[lowestY] )
            lowestY = i;
    }
    carY = wheelY[lowestY]-16;


    // Physics!
    if ( movingLeft == TRUE ){
        if ( velX > 0 ){
            velX = 0;
        }
        velX -= 0.02;
    }
    else if ( movingRight == TRUE ){
        if ( velX < 0 ){
            velX = 0;
        }
        velX += 0.02;
    }
    else {// no outside force{
        if ( int(carX) < 35 ){
            velX += 0.03;
        }
        else if ( int(carX) > 37 ){
            velX -= 0.03;
        }
        else{
            velX = 0;
        }
    }
    if ( velX <= -1.0 ){
            velX = -1.0;
    }
    else if ( velX >= 1.0 ){
            velX = 1.0;
    }
    carX += velX;
    if ( carX < 20 )
        carX = 20.0;
    else if ( carX > 80 )
        carX = 80.0;

    screenX += int(carX/20)+2; // ?
}
void Car::draw()
{
    DrawSprite(carSprite, int(carX), int(carY), FALSE);
    if ( wheelA == TRUE ){
        for(int i = 0; i < 3; i++){
            DrawSprite(wheelSpriteA[i], wheelX[i], wheelY[i], FALSE);
        }
    }
    else{
        for(int i = 0; i < 3; i++){
            DrawSprite(wheelSpriteB[i], wheelX[i], wheelY[i], FALSE);
        }
    }
}

void Car::fire()
{
}

bool Car::moveLeft()
{
    movingLeft = TRUE;
}

bool Car::moveRight()
{
    movingRight = TRUE;
}

void Car::stopMove()
{
    movingLeft = movingRight = FALSE;
}

void Car::jump()
{
}
