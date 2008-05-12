#include "jetfountain.h"

JetFountain::JetFountain()
{
    for(int i = 0; i < 256; i++)
        pList[i] = 0;
    JetX = JetY = decay = 0;
    angle = length = gravity = 0.0;
}

JetFountain::JetFountain(int x, int y, double a, double l, double g)
{
    for(int i = 0; i < 256; i++)
        pList[i] = 0;
    JetX = x;
    JetY = y;
    decay = 1;
    angle = a;
    length = l;
    gravity = g; // downward pull
    isActive = FALSE;
}

JetFountain::~JetFountain()
{
    for(int i = 0; i < 256; i++)
    {
        if (pList[i] != 0)
        {
            delete pList[i];
            pList[i] = 0;
        }
    }
}

void JetFountain::update(int newScroll)
{
    scrollX = newScroll;
    if ( isActive ){
        addJetlet();
    }
    for(int i = 0; i < 256; i++)
    {
        if ( pList[i] != 0 )
        {
            if ( pList[i]->getLife() > 0 )
            {
                pList[i]->update(newScroll);
            }
            else
            {
                delete pList[i];
                pList[i] = 0;
            }
        }
    }
}

void JetFountain::draw()
{
    for(int i = 0; i < 256; i++)
    {
        if ( pList[i] != 0 )
        {
            pList[i]->draw();
        }
    }
}

void JetFountain::setActive(BOOL newActiveState){
    isActive = newActiveState;
}

void JetFountain::addJetlet()
{
    for(int i = 0; i < 256; i++)
    {
        if ( pList[i] == 0 )
        {
            pList[i] = new Particle(JetX, JetY, int(angle+rand()%15), length+rand()%30/10, gravity, 6, "data\\Jetparticle.bmp",JET);
            break;
        }
    }
}
