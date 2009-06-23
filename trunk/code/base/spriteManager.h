#pragma once
#include "gfx.h"
#include <vector>

typedef struct _SpriteData {
    Sprite * sprite;
    char * name;
    int cnt;
} SpriteData;

class SpriteManager{
public:
    SpriteManager();
    ~SpriteManager(); // cleanup the sprite manager efficiently
    Sprite * newSprite(char*); // check list if sprite is already loaded, if so return sprite *
    void removeSprite(Sprite*);// if all instances of sprite have
    int spriteCount(){ return spriteVector.size(); }
    int spritesUsed(Sprite*); // how many sprites in use of this type of sprite?
    void flush(); // removes any unused textures
    void setAutoFlush(bool nFlush){ autoFlush = nFlush; }
private:
    std::vector<SpriteData> spriteVector; // sprite pointer, file name, used count
    bool autoFlush; // should we automatically flush when a sprite is no longer used? (save memory)
};
