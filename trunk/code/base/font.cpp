#include "font.h"
#include "gfx.h"
#include <SDL/SDL.h>

Font::Font(SpriteManager * newManager)
{
    sManager = newManager;
    fontTexture = sManager->newSprite("data\\font.png");
    fontTextureYellow = sManager->newSprite("data\\fonty.png");
}

Font::~Font()
{
    sManager->removeSprite(fontTexture);
    sManager->removeSprite(fontTextureYellow);
}

void Font::drawOrangeNum(int x, int y, int score, int buffer)
{
    drawNum(x,y,score,buffer,true);
}

void Font::drawYellowNum(int x, int y, int score, int buffer)
{
    drawNum(x,y,score,buffer,false);
}

void Font::drawNum(int x, int y, int score, int buffer, bool isOrange)
{
    if ( isOrange == true )
        glBindTexture(GL_TEXTURE_2D, fontTexture->texture);
	else
        glBindTexture(GL_TEXTURE_2D, fontTextureYellow->texture);
	glBegin(GL_QUADS);
	for(int i = 0; i < buffer; i++)
	{
	    int powerOfTen = 1;
	    for(int j = 0; j < (buffer-i-1);j++)
            powerOfTen *= 10;
		int curNum = (score/powerOfTen);
		glTexCoord2f(0.0625f*curNum,0.0f);
		glVertex3i(x+i*8,y,0);

		glTexCoord2f(0.0625f*curNum,1.0f);
		glVertex3i(x+i*8,y+7,0);

		glTexCoord2f(0.0625f*(curNum+1),1.0f);
		glVertex3i(x+i*8+7,y+7,0);

		glTexCoord2f(0.0625f*(curNum+1),0.0f);
		glVertex3i(x+i*8+7,y,0);

		score -= (curNum*powerOfTen);
	}
	glEnd();
}
