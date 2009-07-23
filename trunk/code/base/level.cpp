#include "level.h"
#include "tile1.h"
#include "tile2.h"
#include "tile3.h"
#include "tile4.h"

#include "moonman.h"

int debugLevel[] = {0,1,2,3,3,2,1,1,0,0,0,1,1,1,1,2,2,2,3,3,3,2,2,2,3,3,3,0,1,2,3,3,2,1,1,0,0,0,1,1,1,1,2,2,2,3,3,3,2,2,2,3,3,3,
                    0,1,2,3,3,2,1,0,0,0,4,5,2,3,1,2,2,2,3,3,3,2,2,2,3,3,3,4,6,5,3,3,2,1,0,0,0,0,1,1,1,1,2,2,2,3,3,3,2,2,2,3,3,3,
                    0,1,4,5,3,3,2,0,0,0,0,1,1,1,1,2,2,2,3,3,3,2,2,2,3,3,3,0,1,2,3,3,2,1,0,0,0,0,1,1,1,1,2,2,2,4,6,6,6,6,6,6,6,5};

BOOL debugMoonMen[] = {0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
                    0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,
                    1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0};

int debugBoulders[] = {0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

BOOL debugJetMen[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
                    0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
                    1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

BOOL debugBuses[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
                    0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
                    1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


Level::Level(SpriteManager * newManager)
{
    sManager = newManager;
    tiles[0] = sManager->newSprite("data\\tile1.bmp");
    tiles[1] = sManager->newSprite("data\\tile2.bmp");
    tiles[2] = sManager->newSprite("data\\tile3.bmp");
    tiles[3] = sManager->newSprite("data\\tile4.bmp");
    tiles[4] = sManager->newSprite("data\\pitfall1.bmp");
    tiles[5] = sManager->newSprite("data\\pitfall2.bmp");
    tiles[6] = sManager->newSprite("data\\pitfall3.bmp");
    spaceBG = sManager->newSprite("data\\spacebg1.bmp");
    farBG = sManager->newSprite("data\\farbg1.bmp");
    closeBG = sManager->newSprite("data\\closebg1.bmp");
    levelX=0;
}

Level::~Level()
{
    for(int i = 0; i < 7; i++)
        sManager->removeSprite(tiles[i]);
    sManager->removeSprite(spaceBG);
    sManager->removeSprite(farBG);
    sManager->removeSprite(closeBG);
}
/*
void Level::generateMoonMen(std::vector<MoonMan*> * manArray){
    for ( int i = 0; i < 164; i++){
        if (debugMoonMen[i] == TRUE){
            manArray->push_back(new MoonMan(i*32, sManager));
        }
    }
}

void Level::generateBoulders(std::vector<Boulder*> * boulderArray){
    for ( int i = 0; i < 164; i++){
        if (debugBoulders[i] > 0){
            boulderArray->push_back(new Boulder(i*32,debugBoulders[i]-1, sManager));
        }
    }
}

void Level::generateJetMen(std::vector<JetMan*> * jetArray, std::vector<JetFountain*> *ftnArray){
    for ( int i = 0; i < 164; i++){
        if (debugJetMen[i] == TRUE){
            jetArray->push_back(new JetMan(i*32, sManager));
            ftnArray->push_back(new JetFountain(i*32,jetArray->back()->getY(),270,1,0, sManager));
        }
    }
}

void Level::generateBuses(std::vector<Bus*> * busArray){
    for ( int i = 0; i < 164; i++){
        if (debugBuses[i] == TRUE){
            busArray->push_back(new Bus(i*32, sManager));
        }
    }
}

*/

void Level::update(int scrollX, ActorPool * actorPool, int enemyGroup)
{
    levelX = scrollX;

    if ( debugMoonMen[int(levelX/32)+9] )
    {
        debugMoonMen[int(levelX/32)+9] = 0;
        MoonMan * mMan = new MoonMan(levelX + 288, sManager);
        actorPool->addActor(mMan, enemyGroup);
    }
}

void Level::draw()
{
    int spaceX=levelX%15360;
    int farX=levelX%3840;
    int closeX=levelX%1920;
    // DRAW PARALLAX
    DrawSprite(*spaceBG,-int(spaceX/32), 0, FALSE);
    if ( spaceX > 7680) //15360 - (240*32) )
    {
        DrawSprite(*spaceBG,(15360 - spaceX)/32, 0, FALSE);
    }
    DrawSprite(*farBG,-int(farX/8), 0, FALSE);
    if ( farX > 1920) //3840 - (240*8) )
    {
        DrawSprite(*farBG,(3840 - farX)/8, 0, FALSE);
    }
    DrawSprite(*closeBG,-int(closeX/2), 0, FALSE);
    if ( closeX > 960) //1920 - (240*2) )
    {
        DrawSprite(*closeBG,(1920 - closeX)/2, 0, FALSE);
    }
    for(int i = int(levelX/32); i < int(levelX/32)+9; i++)
    {
        DrawSprite(*tiles[debugLevel[i]], i*32 - levelX, 190, FALSE);
    }
}

BOOL Level::isPit(int x){
    int tileNum = debugLevel[(x/32)];
    if ( tileNum > 3 && tileNum < 7 ){ // 4-6 are pitfalls
        return TRUE;
    }
    else{
        return FALSE;
    }
}

BOOL Level::isGround(int x, int y){
    // first find which "tile" we are looking at with the current x/y
    // Then lookup through our level LUTs, and find if that point is ground
    // or not.
    if ( y < 196 ) return FALSE; // Auto-Fail
    int yOffset = y - 196;
    int tileNum = debugLevel[(x/32)];
    BOOL groundRtn = FALSE;
    unsigned char * tileLUT = 0;
    if ( tileNum == 0 ){
        tileLUT = tile1;
    }
    else if ( tileNum == 1 ){
        tileLUT = tile2;
    }
    else if ( tileNum == 2 ){
        tileLUT = tile3;
    }
    else if ( tileNum == 3 ){
        tileLUT = tile4;
    }
    else{
        return TRUE;
    }
    if ( tileLUT != 0 )
    {
        groundRtn = tileLUT[x%32 + yOffset*32];
    }
    else{
        printf("ERROR! Invalid look up table %i",tileNum);
        groundRtn = TRUE;
    }
    return groundRtn;
}
