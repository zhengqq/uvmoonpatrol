#include "level.h"

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

void Level::update()
{
}

void Level::draw()
{
    for(int i = 0; i < 8; i++){
        DrawSprite(tiles[i%4], i*32, 190, FALSE);
    }
}
