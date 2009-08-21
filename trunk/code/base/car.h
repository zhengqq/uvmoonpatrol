#pragma once

#include "base.h"
#include "gfx.h"

class Car : public Actor
{
public:
    Car(SpriteManager*); // Constructor
    virtual ~Car(); // Deconstructor
    virtual int update(Level*, int); // give this the level terrain?
    virtual void draw();
    virtual int collision(); // what happens during a collision?

    void fire();
    void moveLeft();
    void moveRight();
    void stopMove();
    void jump();
    int getScreenX(){return screenX;}
    virtual int getX(){return int(int(carX)+screenX);}
    virtual int getY(){return int(carY);}
    BOOL isAirBorne(){ return airBorne; }
    virtual int width(){return carSprite->width;}
    virtual int height(){return carSprite->height;}
    void boostUp(){ velY = -5.0; } // give it a boost!
    void slowDown(){ velX -= 2.5; } // slow us down a little
    void causeCrash(){ crashed = TRUE; } // cause a crash!
    BOOL isCrashed(){ return crashed;}

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
    Sprite * carSprite;
    Sprite * wheelSpriteA[3]; // all 3 wheels
    Sprite * wheelSpriteB[3]; // all 3 wheels in second animation
    SpriteManager * sManager;
    int wheelX[3],wheelY[3];
};
