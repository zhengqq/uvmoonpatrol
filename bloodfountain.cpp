#include "bloodfountain.h"

char * bloodList[4] = {"data\\blood1.bmp","data\\blood2.bmp","data\\blood3.bmp","data\\blood4.bmp"};

BloodFountain::BloodFountain()
{
    for(int i = 0; i < 256; i++)
        pList[i] = 0;
    bloodX = bloodY = lifeSpan = decay = 0;
    angle = length = gravity = 0.0;
}

BloodFountain::BloodFountain(int x, int y, double a, double l)
{
    for(int i = 0; i < 256; i++)
        pList[i] = 0;
    bloodX = x;
    bloodY = y;
    lifeSpan = 200;
    decay = 1;
    angle = a;
    length = l;
    gravity = 0.9; // downward pull
}

BloodFountain::~BloodFountain()
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

void BloodFountain::update()
{
    for(int i = 0; i < 256; i++)
    {
        if ( pList[i] != 0 )
        {
            if ( pList[i]->getLife() > 0 )
            {
                pList[i]->update();
            }
            else
            {
                delete pList[i];
                pList[i] = 0;
            }
        }
    }
    addDroplet();
}

void BloodFountain::draw()
{
    for(int i = 0; i < 256; i++)
    {
        if ( pList[i] != 0 )
        {
            pList[i]->draw();
        }
    }
}

void BloodFountain::addDroplet()
{
    for(int i = 0; i < 256; i++)
    {
        if ( pList[i] == 0 )
        {
            pList[i] = new Particle(bloodX, bloodY, 80+rand()%20, 10+rand()%5, gravity, bloodList[rand()%4]);
            break;
        }
    }
}
