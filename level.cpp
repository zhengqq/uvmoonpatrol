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

    spaceX=0;
    farX=0;
    closeX=0;
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
    spaceX++;
    if ( spaceX >= 15360) // 480 * 32
    {
        spaceX = 0;
    }
    DrawSprite(spaceBG,-int(spaceX/32), 0, FALSE);
    farX++;
    if ( farX >= 3840 ) // 480 * 8
    {
        farX = 0;
    }
    DrawSprite(farBG,-int(farX/8), 0, FALSE);
    closeX++;
    if ( closeX >= 1920 )
    {
        closeX = 0;
    }
    DrawSprite(closeBG,-int(closeX/2), 0, FALSE);
    for(int i = 0; i < 164; i++){
        DrawSprite(tiles[debugLevel[i]], i*32 - levelX, 190, FALSE);
    }
}
