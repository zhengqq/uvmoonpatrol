#include "particle.h"
#include <math.h>

#define PI 3.14159265

typedef enum {
    MOVING=0,
    GROUND
};

Particle::Particle()
{
    pX = pY = 0.0;
    pState = GROUND;
}

Particle::Particle(int x, int y, int angle, double length, double g, char * filename)
{
    pState = MOVING;
    pX = double(x);
    pY = double(y);
    vX = length * cos(angle*PI/180);
    vY = length * sin(angle*PI/180);
    gravity = g;
    groundLife = 90;
    generateSprite(filename, &pSprite);
}

Particle::~Particle()
{
    glDeleteTextures( 1, &pSprite.texture );
}

void Particle::update()
{
    if ( pState == MOVING )
    {
        vY -= gravity;
        pX += vX;
        pY -= vY;
        if ( pY >= 200 )
        {
            pState = GROUND;
            pY = 200;
        }
    }
    else if ( pState == GROUND )
    {
        if ( groundLife > 0 ){
            groundLife--;
        }
    }
}

void Particle::draw()
{
     DrawSprite(pSprite, int(pX), int(pY), FALSE);
}
