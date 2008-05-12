#include "gfx.h"
#include "base.h"

int InitGL(void)			// All Setup For OpenGL Goes Here
{
	glViewport(0, 0,240, 248);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0.0f, 1.0f); // 0,w,h,0 makes it top left,  0,w,0,h makes it bottom left
	//gluOrtho2D(0,240,0,248);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return TRUE;						// Initialization Went OK
}

SDL_Surface *LoadBMP2RGBA(char *filename)
{
  Uint8 *rowhi, *rowlo;
  Uint8 *tmpbuf, tmpch;
  SDL_Surface *image;
  int i, j;
  image = SDL_LoadBMP(filename);
  if ( image == NULL ) {
    fprintf(stderr, "Unable to load %s: %s\n", filename, SDL_GetError());
    return(NULL);
  }
  /* Copy our RGB into an ABGR buffer - C32 */
  // Allocated all 4 pixels for our ABGR
    unsigned char * newPixels = (unsigned char *)malloc((image->w*image->h*4));
    unsigned char * newPixelPtr = newPixels;
    unsigned char * pixelPtr = (unsigned char *)image->pixels;
    for(int i = 0; i < (image->w*image->h);i++) // Also flips RGB to ABGR
    {
        if ( (*pixelPtr) == KEY_B && (*(pixelPtr+1)) == KEY_G && (*(pixelPtr+2)) == KEY_R ){
            *((unsigned long*)newPixelPtr) = (*pixelPtr)<<16 | (*(pixelPtr+1))<<8 | (*(pixelPtr+2));
        }
        else{
            *((unsigned long*)newPixelPtr) = 255<<24 | (*pixelPtr)<<16 | (*(pixelPtr+1))<<8 | (*(pixelPtr+2));
        }
        pixelPtr += sizeof(unsigned char)*3;
        newPixelPtr += sizeof(unsigned char)*4;
    }
    free(image->pixels);        // free the pixels used in the original LoadBMP
    image->pixels = newPixels;  // set our current image pixels to our new pixels
    image->pitch = (image->pitch/3)*4; // adjust our pitch for 4 pixels instead of 3
    // Now flip our surface for OpenGL specifics!
    tmpbuf = (Uint8 *)malloc(image->pitch);
    if ( tmpbuf == NULL ) {
        fprintf(stderr, "Out of memory\n");
        return(NULL);
    }
    rowhi = (Uint8 *)image->pixels; // highest portion of the image
    rowlo = rowhi + (image->h * image->pitch) - image->pitch; // lowest portion
    for ( i=0; i<image->h/2; ++i ) {
        memcpy(tmpbuf, rowhi, image->pitch);
        memcpy(rowhi, rowlo, image->pitch);
        memcpy(rowlo, tmpbuf, image->pitch);
        rowhi += image->pitch;
        rowlo -= image->pitch;
    }
  return(image);
}

BOOL generateSprite(char * filename, Sprite * sprite)
{
    SDL_Surface * tmpImage = LoadBMP2RGBA(filename);
    if ( tmpImage == NULL ){
        return FALSE;
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
    return TRUE;
}

void DrawSprite(Sprite & sprite, int x, int y, bool flip)
{
//	if(x>camera_x+160 || y>camera_y+120 || x+sprite.width<camera_x-160 || y+sprite.height<camera_y-120)
//		return;
	float xflip=0.0f;
	if(flip) xflip=1.0f;
	glBindTexture(GL_TEXTURE_2D, sprite.texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f+xflip, 1.0f);
	glVertex3i(x, y, 0);
	glTexCoord2f(0.0f+xflip, 0.0f);
	glVertex3i(x, y+sprite.height, 0);
	glTexCoord2f(1.0f-xflip, 0.0f);
	glVertex3i(x+sprite.width, y+sprite.height, 0);
	glTexCoord2f(1.0f-xflip, 1.0f);
	glVertex3i(x+sprite.width, y, 0);
	glEnd();
}
