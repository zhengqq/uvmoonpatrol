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
    for(int i = 0; i < 164; i++){
        DrawSprite(tiles[debugLevel[i]], i*32 - levelX, 190, FALSE);
    }
}
