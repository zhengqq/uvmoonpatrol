#ifndef __BLOODFOUNTAIN_H__
#define __BLOODFOUNTAIN_H__

#include "particle.h"

class BloodFountain
{
public:
    BloodFountain();
    BloodFountain(int,int,double,double,int,double);
    ~BloodFountain();
    void update(int);
    void draw();
    void setSpurting(); // default spurting fountain
    void setCloud();    // set our fountain to a cloud
    void setPop();
    int getLife(){return lifeSpan;}
private:
    void addDroplet();
    Particle * pList[256]; // particle list for our blood sprites
    int scrollX;
    int bloodX, bloodY; // Where is the fountain spewing from?
    int lifeSpan;       // how long do we want the fountain to last?
    int decay;          // How much decay on the life span do we want? (1.0 ?)
    double angle;       // angle of our blood fountain
    double length;      // initial length of our blood fountain vector
    double gravity;     // gravity applying to our blood fountain
    unsigned int type;
};

#endif // __BLOODFOUNTAIN_H__
