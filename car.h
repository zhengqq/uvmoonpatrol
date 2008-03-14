#ifndef __CAR_H__
#define __CAR_H__

#include "base.h"
#include "gfx.h"

class Car
{
public:
    Car(); // Constructor
    ~Car(); // Deconstructor
    void update(); // give this the level terrain?
    void draw();
    void fire();
    bool moveLeft();
    bool moveRight();
    void stopMove();
    void jump();
    int getScreenX(){return screenX;}
    int getX(){return int(carX+screenX);}
    int getY(){return carY;}
    int width(){return carSprite.width;}
    int height(){return carSprite.height;}
private:
    unsigned int currentFrame; // what frame are we at? (used for making wheels spin)
    BOOL wheelA;
    int speed;
    int carX, screenX, carY; // where are we in the world?
    unsigned int fireCount; // how long since the last time we fired?
    BOOL airBorne,movingLeft,movingRight; // are we airborne?
    Sprite carSprite;
    Sprite wheelSpriteA[3]; // all 3 wheels
    Sprite wheelSpriteB[3]; // all 3 wheels in second animation
};

#endif // __CAR_H__
