#include "gfx.h"

int InitGL(void)			// All Setup For OpenGL Goes Here
{
	glViewport(0, 0,SCREEN_WIDTH, SCREEN_HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH, GAME_HEIGHT, 0, 0.0f, 1.0f); // 0,w,h,0 makes it top left,  0,w,0,h makes it bottom left
	//gluOrtho2D(0,240,0,248);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;						// Initialization Went OK
}

SDL_Surface *LoadIMG2RGBA(char *filename)
{
    SDL_Surface *orig,*image;

    SDL_PixelFormat RGBAFormat;
	RGBAFormat.palette = 0; RGBAFormat.colorkey = 0; RGBAFormat.alpha = 0;
	RGBAFormat.BitsPerPixel = 32; RGBAFormat.BytesPerPixel = 4;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	RGBAFormat.Rmask = 0xFF000000; RGBAFormat.Rshift =  0; RGBAFormat.Rloss = 0;
	RGBAFormat.Gmask = 0x00FF0000; RGBAFormat.Gshift =  8; RGBAFormat.Gloss = 0;
	RGBAFormat.Bmask = 0x0000FF00; RGBAFormat.Bshift = 16; RGBAFormat.Bloss = 0;
	RGBAFormat.Amask = 0x000000FF; RGBAFormat.Ashift = 24; RGBAFormat.Aloss = 0;
#else
	RGBAFormat.Rmask = 0x000000FF; RGBAFormat.Rshift = 24; RGBAFormat.Rloss = 0;
	RGBAFormat.Gmask = 0x0000FF00; RGBAFormat.Gshift = 16; RGBAFormat.Gloss = 0;
	RGBAFormat.Bmask = 0x00FF0000; RGBAFormat.Bshift =  8; RGBAFormat.Bloss = 0;
	RGBAFormat.Amask = 0xFF000000; RGBAFormat.Ashift =  0; RGBAFormat.Aloss = 0;
#endif

    orig = IMG_Load(filename);
    if ( orig == NULL ) {
        fprintf(stderr, "Unable to load %s: %s\n", filename, SDL_GetError());
        return(NULL);
    }

    image = SDL_ConvertSurface(orig, &RGBAFormat, SDL_OPENGL); // Converts all surfaces to RGBA
    SDL_FreeSurface(orig);

    return(image);
}

// Automatically detect non-power of 2 (instead of 8x8, 16x16, 32x32, 64x64, 128x128, etc.)
// and fill in buffer will be the next step for this function.
bool generateSprite(char * filename, Sprite * sprite)
{
    SDL_Surface * tmpImage;
    if ( strlen(filename) < 4 )
        return false;
    char * extension = filename;
    extension += (strlen(filename)-4);

    tmpImage = LoadIMG2RGBA(filename); // Use SDL_Image
    if ( tmpImage == NULL ){
        fprintf(stderr, "IMG_LOAD: %s\n", IMG_GetError());
        return false;
    }

    glGenTextures(1, &sprite->texture);		// Create The Texture
    glBindTexture(GL_TEXTURE_2D, sprite->texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tmpImage->w, tmpImage->h,
        0, GL_RGBA, GL_UNSIGNED_BYTE, tmpImage->pixels);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    sprite->width = tmpImage->w;
    sprite->height = tmpImage->h;
    if (tmpImage) {		// If Texture Exists
        SDL_FreeSurface(tmpImage);
    }
    return true;
}

void DrawSprite(Sprite & sprite, int x, int y, bool flip)
{
//	if(x>camera_x+160 || y>camera_y+120 || x+sprite.width<camera_x-160 || y+sprite.height<camera_y-120)
//		return;
	float xflip=0.0f;
	if(flip) xflip=1.0f;
    glBindTexture(GL_TEXTURE_2D, sprite.texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f+xflip, 0.0f);
	glVertex3i(x, y, 0);
	glTexCoord2f(0.0f+xflip, 1.0f);
	glVertex3i(x, y+sprite.height, 0);
	glTexCoord2f(1.0f-xflip, 1.0f);
	glVertex3i(x+sprite.width, y+sprite.height, 0);
	glTexCoord2f(1.0f-xflip, 0.0f);
	glVertex3i(x+sprite.width, y, 0);
	glEnd();
}

void DrawScaledSprite(Sprite & sprite, int x, int y, int width, int height, bool flip)
{
//	if(x>camera_x+160 || y>camera_y+120 || x+sprite.width<camera_x-160 || y+sprite.height<camera_y-120)
//		return;
	float xflip=0.0f;
	if(flip) xflip=1.0f;
    glBindTexture(GL_TEXTURE_2D, sprite.texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f+xflip, 0.0f);
	glVertex3i(x, y, 0);
	glTexCoord2f(0.0f+xflip, 1.0f);
	glVertex3i(x, y+height, 0);
	glTexCoord2f(1.0f-xflip, 1.0f);
	glVertex3i(x+width, y+height, 0);
	glTexCoord2f(1.0f-xflip, 0.0f);
	glVertex3i(x+width, y, 0);
	glEnd();
}
