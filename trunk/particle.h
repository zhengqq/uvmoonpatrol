#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "base.h"
#include "gfx.h"

class Particle
{
public:
    Particle();
    Particle(int, int, int, double, double, char *); // x,y,angle,length,gravity,sprite name
    ~Particle();
    void update(); // update our particles x & y values
    void draw(); // draw the particle
    unsigned int getLife() { return groundLife; }
private:
    unsigned int pState;
    unsigned int groundLife; // tells it how long to stay on the ground
    double pX,pY;   // particle's x & y
    double vX,vY;
    double gravity;
    Sprite pSprite; // particle's sprite
};

#endif // __PARTICLE_H__
