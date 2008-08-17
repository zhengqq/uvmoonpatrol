#ifndef _FONT_H_
#define _FONT_H_

#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library

#include "gfx.h"

class Font
{
public:
	Font();
	~Font();
	void drawOrangeNum(int,int,int,int);
    void drawYellowNum(int,int,int,int);
private:
    void drawNum(int,int,int,int,bool); // x, y, actual number, buffer (0000, 000, 00, 0) same as /x08 :D
	Sprite fontTexture;
	Sprite fontTextureYellow;
};

#endif
