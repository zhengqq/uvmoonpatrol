#ifndef __JETFOUNTAIN_H__
#define __JETFOUNTAIN_H__

#include "particle.h"

class JetFountain
{
public:
    JetFountain();
    JetFountain(int,int,double,double,double);
    ~JetFountain();
    void update(int);
    void draw();
    void setPosition(int newX,int newY){ JetX = newX; JetY = newY;}
    void setActive(BOOL);
private:
    void addJetlet(); // droplet?
    Particle * pList[256]; // particle list for our blood sprites
    BOOL isActive;
    int scrollX;
    int JetX, JetY; // Where is the fountain spewing from?
    int decay;          // How much decay on the life span do we want? (1.0 ?)
    double angle;       // angle of our blood fountain
    double length;      // initial length of our blood fountain vector
    double gravity;     // gravity applying to our blood fountain
};

#endif // __JETFOUNTAIN_H__
