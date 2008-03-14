#include "bloodfountain.h"

char * bloodList[4] = {"data\\blood1.bmp","data\\blood2.bmp","data\\blood3.bmp","data\\blood4.bmp"};

BloodFountain::BloodFountain()
{
    for(int i = 0; i < 256; i++)
        pList[i] = 0;
    bloodX = bloodY = lifeSpan = decay = 0;
    angle = length = gravity = 0.0;
}

BloodFountain::BloodFountain(int x, int y, double a, double l, int life, double g)
{
    for(int i = 0; i < 256; i++)
        pList[i] = 0;
    bloodX = x;
    bloodY = y;
    lifeSpan = life;
    decay = 1;
    angle = a;
    length = l;
    gravity = g; // downward pull
    type = FOUNTAIN; // default
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

void BloodFountain::setSpurting()
{
    type = FOUNTAIN;
}

void BloodFountain::setCloud()
{
    type = CLOUD;
}

void BloodFountain::setPop()
{
    type = POP;
}

void BloodFountain::update(int newScroll)
{
    scrollX = newScroll;
    if ( lifeSpan > 0 )
    {
        if ( type == FOUNTAIN )
        {
            addDroplet();
        }
        else if ( type == CLOUD )
        {
            for(int i = 0; i < rand()%2+2; i++){
                addDroplet();
            }
        }
        else if ( type == POP )
        {
            for(int i = 0; i < 8; i++){
                addDroplet();
            }
        }
        lifeSpan--;
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
            if ( type == FOUNTAIN )
            {
                pList[i] = new Particle(bloodX, bloodY, 80+rand()%20, 10+rand()%5, gravity, 90, bloodList[rand()%4],FOUNTAIN);
            }
            else if ( type == CLOUD )
            {
                pList[i] = new Particle(bloodX+(rand()%20-10), bloodY+(rand()%20-10), 5-rand()%10, 1.0, gravity, 15, bloodList[rand()%4],CLOUD);
            }
            else if ( type == POP )
            {
                pList[i] = new Particle(bloodX, bloodY, rand()%360, 0.5+(rand()%10/10), gravity, 25, bloodList[rand()%4],POP);
            }
            break;
        }
    }
}
