#ifndef __JETMAN_H__
#define __JETMAN_H__

#include <vector>
#include "base.h"
#include "gfx.h"
#include "jetfountain.h"

class JetMan{
public:
    JetMan();
    JetMan(int);
    ~JetMan();
    void update(int,std::vector<JetFountain>::iterator,int,int);
    void draw();
    int getX(){return int(jetX);}
    int getY(){return int(jetY);}
    int width(){return jetSprite.width;}
    int height(){return jetSprite.height;}
private:
    int state;
    int swoopCount;
    Sprite jetSprite;
    int scrollX;
    double velX,velY,gravity,jetX,jetY;
};

#endif // __JETMAN_H__
