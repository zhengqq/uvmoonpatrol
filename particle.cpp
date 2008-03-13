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

Particle::Particle(int x, int y, int angle, double length, double g, int l, char * filename, unsigned int type)
{
    pState = MOVING;
    pType = type;
    pX = double(x);
    pY = double(y);
    vX = length * cos(angle*PI/180);
    vY = length * sin(angle*PI/180);
    gravity = g;
    life = l;
    generateSprite(filename, &pSprite);
}

Particle::~Particle()
{
    glDeleteTextures( 1, &pSprite.texture );
}

void Particle::update()
{
    if ( pType == FOUNTAIN)
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
            if ( life > 0 ){
                life--;
            }
        }
    }
    else if ( pType == CLOUD )
    {
        pX += vX;
        pY -= vY;
        life--;
    }
}

void Particle::draw()
{
     DrawSprite(pSprite, int(pX), int(pY), FALSE);
}
