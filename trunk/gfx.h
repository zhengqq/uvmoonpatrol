#ifndef __GFX_H__
#define __GFX_H__

#include <SDL/SDL.h>
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include "base.h"

// Sprite - DrPetter from 7th Swarming
struct Sprite
{
	GLuint texture;
	int width;
	int height;
};

SDL_Surface *LoadBMP2RGBA(char *filename);
void DrawSprite(Sprite & sprite, int x, int y, bool flip);
BOOL generateSprite(char * filename, Sprite * sprite);

#endif // __GFX_H__
