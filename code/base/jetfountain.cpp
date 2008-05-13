#include "jetfountain.h"

JetFountain::JetFountain()
{
    JetX = JetY = decay = 0;
    angle = length = gravity = 0.0;
}

JetFountain::JetFountain(int x, int y, double a, double l, double g)
{
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
    while(!pList.empty()){
        delete pList.back(); pList.pop_back();
    }
}

void JetFountain::update(int newScroll)
{
    scrollX = newScroll;
    if ( isActive ){
        addJetlet();
    }
    std::vector<Particle*>::iterator pIter = pList.begin();
    while(pIter != pList.end()){
        Particle * p = *(pIter);
        if ( p->getLife() > 0){
            p->update(newScroll);
            ++pIter;
        }
        else{
            pIter = pList.erase(pIter);
        }
    }
}

void JetFountain::draw()
{
    std::vector<Particle*>::iterator pIter = pList.begin();
    while(pIter != pList.end()){
        Particle * p = *(pIter);
        p->draw();
        ++pIter;
    }
}

void JetFountain::setActive(BOOL newActiveState){
    isActive = newActiveState;
}

void JetFountain::addJetlet()
{
    pList.push_back(new Particle(JetX, JetY, int(angle+rand()%15), length+rand()%30/10, gravity, 6, "data\\Jetparticle.bmp",JET));
}
