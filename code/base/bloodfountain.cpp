#include "bloodfountain.h"

// These defines tell the blood particle explosion how many max
//  blood droplets for each we can have before it starts slowing down.
#define MAX_FOUNTAIN 128
#define MAX_CLOUD 64
#define MAX_POP 48

char * bloodList[4] = {"data\\blood1.bmp","data\\blood2.bmp","data\\blood3.bmp","data\\blood4.bmp"};

BloodFountain::BloodFountain()
{
    bloodX = bloodY = lifeSpan = decay = 0;
    angle = length = gravity = 0.0;
}

BloodFountain::BloodFountain(int x, int y, double a, double l, int life, double g)
{
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
    while (!pList.empty()){
        delete pList.back(); pList.pop_back();
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
            if ( pList.size() < MAX_FOUNTAIN ){
                for(int i = 0; i < 3; i++){
                    addDroplet();
                }
            }
        }
        else if ( type == CLOUD )
        {
            if ( pList.size() < MAX_CLOUD ){
                for(int i = 0; i < rand()%2+2; i++){
                    addDroplet();
                }
            }
        }
        else if ( type == POP )
        {
            if ( pList.size() < MAX_POP ){
                for(int i = 0; i < 8; i++){
                    addDroplet();
                }
            }
        }
        lifeSpan--;
    }
    std::vector<Particle*>::iterator pIter = pList.begin();
    while( pIter != pList.end()){
        Particle * p = *(pIter);
        if ( p->getLife() > 0 ){
            p->update(newScroll);
            ++pIter;
        }
        else{
            pIter = pList.erase(pIter);
        }
    }
}

void BloodFountain::draw()
{
    std::vector<Particle*>::iterator pIter = pList.begin();
    while ( pIter != pList.end()){
        Particle * p = *(pIter);
        p->draw();
        ++pIter;
    }
}

void BloodFountain::addDroplet()
{
    if ( type == FOUNTAIN )
    {
        pList.push_back(new Particle(bloodX, bloodY, int(angle+rand()%20), length+rand()%5, gravity, 90, bloodList[rand()%4],FOUNTAIN));
    }
    else if ( type == CLOUD )
    {
        pList.push_back(new Particle(bloodX+(rand()%20-10), bloodY+(rand()%20-10), int(angle-rand()%10), length, gravity, 15, bloodList[rand()%4],CLOUD));
    }
    else if ( type == POP )
    {
        pList.push_back(new Particle(bloodX, bloodY, rand()%360, length+(rand()%10/10), gravity, 25, bloodList[rand()%4],POP));
    }
}
