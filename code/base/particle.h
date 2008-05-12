#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "base.h"
#include "gfx.h"

typedef enum {
    FOUNTAIN=0,
    CLOUD,
    POP,
    JET
};

class Particle
{
public:
    Particle();
    Particle(int, int, int, double, double, int, char *, unsigned int); // x,y,angle,length,gravity,life,sprite name,type
    ~Particle();
    void update(int); // update our particles x & y values
    void draw(); // draw the particle
    unsigned int getLife() { return life; }
private:
    unsigned int pState;
    unsigned int pType;
    int scrollX;
    int life,maxLife; // tells it how long to stay on the ground
    double pX,pY;   // particle's x & y
    double vX,vY;
    double gravity;
    Sprite pSprite; // particle's sprite
};

#endif // __PARTICLE_H__
