#include "level.h"

int debugLevel[] = {0,1,2,3,3,2,1,0,0,0,0,1,1,1,1,2,2,2,3,3,3,2,2,2,3,3,3,0,1,2,3,3,2,1,0,0,0,0,1,1,1,1,2,2,2,3,3,3,2,2,2,3,3,3,
                    0,1,2,3,3,2,1,0,0,0,0,1,1,1,1,2,2,2,3,3,3,2,2,2,3,3,3,0,1,2,3,3,2,1,0,0,0,0,1,1,1,1,2,2,2,3,3,3,2,2,2,3,3,3,
                    0,1,2,3,3,2,1,0,0,0,0,1,1,1,1,2,2,2,3,3,3,2,2,2,3,3,3,0,1,2,3,3,2,1,0,0,0,0,1,1,1,1,2,2,2,3,3,3,2,2,2,3,3,3};

Level::Level()
{
    if(!generateSprite("data\\tile1.bmp",&tiles[0])){
        printf("Could not load tile1.bmp\n");
    }
    if(!generateSprite("data\\tile2.bmp",&tiles[1])){
        printf("Could not load tile2.bmp\n");
    }
    if(!generateSprite("data\\tile3.bmp",&tiles[2])){
        printf("Could not load tile3.bmp\n");
    }
    if(!generateSprite("data\\tile4.bmp",&tiles[3])){
        printf("Could not load tile4.bmp\n");
    }
    if(!generateSprite("data\\spacebg1.bmp",&spaceBG)) printf("Could not load spacebg1.bmp\n");
    if(!generateSprite("data\\farbg1.bmp",&farBG)) printf("Could not load farbg1.bmp\n");
    if(!generateSprite("data\\closebg1.bmp",&closeBG)) printf("Could not load closebg1.bmp\n");
    levelX=0;
}

Level::~Level()
{
    for(int i = 0; i < 4; i++)
    {
        glDeleteTextures(1, &tiles[i].texture);
    }
}

void Level::update(int scrollX)
{
    levelX = scrollX;
}

void Level::draw()
{
    int spaceX=levelX%15360;
    int farX=levelX%3840;
    int closeX=levelX%1920;
    // DRAW PARALLAX
    DrawSprite(spaceBG,-int(spaceX/32), 0, FALSE);
    if ( spaceX > 7680) //15360 - (240*32) )
    {
        DrawSprite(spaceBG,(15360 - spaceX)/32, 0, FALSE);
    }
    DrawSprite(farBG,-int(farX/8), 0, FALSE);
    if ( farX > 1920) //3840 - (240*8) )
    {
        DrawSprite(farBG,(3840 - farX)/8, 0, FALSE);
    }
    DrawSprite(closeBG,-int(closeX/2), 0, FALSE);
    if ( closeX > 960) //1920 - (240*2) )
    {
        DrawSprite(closeBG,(1920 - closeX)/2, 0, FALSE);
    }
    // FINISH PARALLAX
    for(int i = 0; i < 164; i++){
        DrawSprite(tiles[debugLevel[i]], i*32 - levelX, 190, FALSE);
    }
}

BOOL Level::isGround(int x, int y){
    // first find which "tile" we are looking at with the current x/y
    // Then lookup through our level LUTs, and find if that point is ground
    // or not.
    if ( y < 196 ) return FALSE; // Auto-Fail
    int yOffset = y - 196;
    int tileNum = debugLevel[x/32];
    BOOL groundRtn = tileLUT[tileNum][x%32 + yOffset*32];
    return groundRtn;
}