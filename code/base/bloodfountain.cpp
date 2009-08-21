#include "bloodfountain.h"

#define MAX_FOUNTAIN 256
#define MAX_CLOUD 256
#define MAX_POP 256

#define LIFE_FOUNTAIN 90
#define LIFE_CLOUD 15
#define LIFE_POP 20

char * bloodList[6] = {"data\\blood1.png","data\\blood2.png","data\\blood3.png","data\\blood4.png","data\\guts1.png","data\\guts2.png"};

BloodFountain::BloodFountain()
{
    bloodX = bloodY = lifeSpan = decay = 0;
    angle = length = gravity = 0.0;
}

BloodFountain::BloodFountain(int x, int y, double a, double l, int life, double g, SpriteManager * newManager)
{
    sManager = newManager;
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
                for(int i = 0; i < 6; i++){
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
        pList.push_back(new Particle(bloodX, bloodY, int(angle+rand()%20), length+rand()%5, gravity, LIFE_FOUNTAIN, bloodList[rand()%4],FOUNTAIN, sManager));
    }
    else if ( type == CLOUD )
    {
        pList.push_back(new Particle(bloodX+(rand()%20-10), bloodY+(rand()%20-10), int(angle-rand()%10), length, gravity, LIFE_CLOUD, bloodList[rand()%4],CLOUD, sManager));
    }
    else if ( type == POP )
    {
        pList.push_back(new Particle(bloodX, bloodY, rand()%360, length+(rand()%10/10), gravity, LIFE_POP, bloodList[rand()%6],POP, sManager));
    }
}
