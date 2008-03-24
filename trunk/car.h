#ifndef __CAR_H__
#define __CAR_H__

#include "base.h"
#include "gfx.h"
#include "level.h"

class Car
{
public:
    Car(); // Constructor
    ~Car(); // Deconstructor
    void update(Level*); // give this the level terrain?
    void draw();
    void fire();
    bool moveLeft();
    bool moveRight();
    void stopMove();
    void jump();
    int getScreenX(){return screenX;}
    int getX(){return int(int(carX)+screenX);}
    int getY(){return int(carY);}
    BOOL isAirBorne(){ return airBorne; }
    int width(){return carSprite.width;}
    int height(){return carSprite.height;}
    void boostUp(){ velY = -5.0; } // give it a boost!
    void slowDown(){ velX -= 2.5; } // slow us down a little
private:
    unsigned int currentFrame; // what frame are we at? (used for making wheels spin)
    BOOL wheelA;
    BOOL crashed; // have we crashed?
    int speed;
    int screenX;
    float carX, carY; // where are we in the world?
    float velX,velY;
    unsigned int fireCount; // how long since the last time we fired?
    BOOL airBorne,jumping,movingLeft,movingRight; // are we airborne?
    Sprite carSprite;
    Sprite wheelSpriteA[3]; // all 3 wheels
    Sprite wheelSpriteB[3]; // all 3 wheels in second animation
    int wheelX[3],wheelY[3];
};

#endif // __CAR_H__
