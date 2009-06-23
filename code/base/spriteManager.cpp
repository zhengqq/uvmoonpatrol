#include "spriteManager.h"
# define START_SIZE 16

SpriteManager::SpriteManager(){
    spriteVector.resize(START_SIZE);
    for(int i = 0; i < START_SIZE; i++){
        spriteVector[i].sprite = NULL;
        spriteVector[i].name = NULL;
        spriteVector[i].cnt = 0;
    }
    autoFlush = false; // do not automatically flush an unused texture
}

SpriteManager::~SpriteManager(){
    for(unsigned int i = 0; i < spriteVector.size(); i++){
        if ( spriteVector[i].sprite != NULL ){
            removeSprite(spriteVector[i].sprite);
        }
    }
}

Sprite * SpriteManager::newSprite(char* newSpriteName){
    unsigned int i;
    for(i=0; i < spriteVector.size(); ++i){
        if ((spriteVector[i].name != NULL) && (!strncmp(spriteVector[i].name, newSpriteName, strlen(newSpriteName)))){
            spriteVector[i].cnt++; // we have another count on this sprite
            return spriteVector[i].sprite;
        }
    }
    Sprite * newSprite = new Sprite;
    if( generateSprite(newSpriteName,newSprite)){
        bool needResize=true;
        for(i=0;i<spriteVector.size();++i){
            if(spriteVector[i].sprite == NULL){
                needResize=false;
                spriteVector[i].sprite = newSprite;
                char * newName = new char[strlen(newSpriteName)];
                strncpy(newName, newSpriteName, strlen(newSpriteName));
                spriteVector[i].name = newName;
                spriteVector[i].cnt = 1;
                break;
            }
        }
        if(needResize==true){
            int oldSize=spriteVector.size();
            spriteVector.resize(oldSize+16); // give us another 16 slots
#ifdef _DEBUG
            //fprintf(stdout, "Resizing Vector to %i\n", spriteVector.size());
#endif
            for(i=oldSize;i<spriteVector.size();i++){
                spriteVector[i].sprite = NULL;
                spriteVector[i].name = NULL;
                spriteVector[i].cnt = 0;
            }
            spriteVector[oldSize].sprite = newSprite;
            char * newName = new char[strlen(newSpriteName)];
            strncpy(newName, newSpriteName, strlen(newSpriteName));
            spriteVector[oldSize].name = newName;
            spriteVector[oldSize].cnt = 1;
        }
        return newSprite;
    }
    else{
        fprintf(stderr, "ERROR: *** Could not generate sprite %s\n", newSpriteName);
        return NULL;
    }
}

void SpriteManager::removeSprite(Sprite* remSprite){
    for(unsigned int i=0; i < spriteVector.size(); ++i){
        if(spriteVector[i].sprite == remSprite){
            spriteVector[i].cnt--; // just reduce the number of sprites associated to this value
            if ( autoFlush || spriteVector[i].cnt == 0 ){
                glDeleteTextures(1, &spriteVector[i].sprite->texture);
                delete spriteVector[i].sprite;
                spriteVector[i].sprite = NULL;
                delete spriteVector[i].name;
                spriteVector[i].name = NULL;
            }
        }
    }
}

void SpriteManager::flush(){
    // Clean any unused sprites
    for(unsigned int i=0; i < spriteVector.size(); ++i){
        if ( spriteVector[i].cnt == 0){
            // call an OpenGL free
            glDeleteTextures(1, &spriteVector[i].sprite->texture);
            delete spriteVector[i].sprite;
            spriteVector[i].sprite = NULL;
            delete spriteVector[i].name;
            spriteVector[i].name = NULL;
        }
    }
}

int SpriteManager::spritesUsed(Sprite*){
    return 0;
}
