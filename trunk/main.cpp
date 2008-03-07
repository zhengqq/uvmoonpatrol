/*	ball3d.c
	Adopted from the code created by Banu Cosmin aka Choko - 20 may 2000
 */

#include <math.h>
#include <stdio.h>
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <SDL/SDL.h>
#include <cstdlib>
#include <ctime>

#define BOOL    int
#define FALSE   0
#define TRUE    1
#define COLORKEY 0,255,0 // transparent color
// Physics iterations per second
#define PHYSICSFPS 30

int         gLastTick;
Uint8*		keys;			// Array Used For The Keyboard Routine
BOOL		active=TRUE;		// Window Active Flag Set To TRUE By Default
BOOL		fullscreen=FALSE;	// Fullscreen Flag Set To Fullscreen Mode By Default

struct Sprite
{
	GLuint texture;
	int width;
	int height;
	int x;
	int y;
};

Sprite		sprites[4];			// 4 Textures

SDL_Surface *LoadBMP(char *filename)
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

  /* GL surfaces are upsidedown and RGB, not BGR :-) */
  tmpbuf = (Uint8 *)malloc(image->pitch);
  if ( tmpbuf == NULL ) {
    fprintf(stderr, "Out of memory\n");
    return(NULL);
  }
  rowhi = (Uint8 *)image->pixels;
  rowlo = rowhi + (image->h * image->pitch) - image->pitch;
  for ( i=0; i<image->h/2; ++i ) {
    for ( j=0; j<image->w; ++j ) {
	tmpch = rowhi[j*3];
	rowhi[j*3] = rowhi[j*3+2];
	rowhi[j*3+2] = tmpch;
	tmpch = rowlo[j*3];
	rowlo[j*3] = rowlo[j*3+2];
	rowlo[j*3+2] = tmpch;
    }
    memcpy(tmpbuf, rowhi, image->pitch);
    memcpy(rowhi, rowlo, image->pitch);
    memcpy(rowlo, tmpbuf, image->pitch);
    rowhi += image->pitch;
    rowlo -= image->pitch;
  }
  free(tmpbuf);
  return(image);
}

int LoadGLTextures() 		// Load Bitmaps And Convert To Textures
{
    int Status=FALSE;		// Status Indicator
    int loop;
    SDL_Surface *TextureImage[4];	// Create Storage Space For The Textures
    memset(TextureImage,0,sizeof(void *)*4);	// Set The Pointer To NULL
    if ((TextureImage[0]=LoadBMP("data\\car.bmp")) &&  // Load The Floor Texture
        (TextureImage[1]=LoadBMP("data\\wheel1_1.bmp")) &&	  // Load the Light Texture
        (TextureImage[2]=LoadBMP("data\\wheel2_1.bmp")) &&
        (TextureImage[3]=LoadBMP("data\\wheel3_1.bmp")))  // Load the Wall Texture
    {
        Status=TRUE;
        for (loop=0; loop<4; loop++) {		// Loop Through 3 Textures
            glGenTextures(1, &sprites[loop].texture);		// Create The Texture
            glBindTexture(GL_TEXTURE_2D, sprites[loop].texture);
            gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TextureImage[loop]->w, TextureImage[loop]->h, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->pixels);
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureImage[loop]->w, TextureImage[loop]->h,
            //    0, GL_RGBA, GL_UNSIGNED_BYTE, TextureImage[loop]->pixels);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
            sprites[loop].width = TextureImage[loop]->w;
            sprites[loop].height = TextureImage[loop]->h;
            sprites[loop].x = sprites[loop].y = 0; // ### DEBUG! ###
            /* ZOMG! */
            unsigned char * pixelR = (unsigned char *)TextureImage[loop]->pixels;
            unsigned char * pixelG = pixelR + sizeof(unsigned char);
            unsigned char * pixelB = pixelG + sizeof(unsigned char);
            for(int i=0; i < TextureImage[loop]->w*TextureImage[loop]->h; i++)
            {
                printf("%06x\n", (*pixelR<<16|*pixelG<<8|*pixelB));
                pixelR += sizeof(unsigned char)*3;
                pixelG += sizeof(unsigned char)*3;
                pixelB += sizeof(unsigned char)*3;
            }
        }
        for (loop=0; loop<4; loop++) {		// Loop Through 3 Textures
            if (TextureImage[loop]) {		// If Texture Exists
                SDL_FreeSurface(TextureImage[loop]);
            }
        }
    }
    return Status;
}

int InitGL(GLvoid)			// All Setup For OpenGL Goes Here
{
  if (!LoadGLTextures())		// If Loading The Textures Failed
    return FALSE;

	glViewport(0, 0,240, 248);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0,240, 0,248, 1.0f, -1.0f);
	gluOrtho2D(0,240,0,248);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return TRUE;						// Initialization Went OK
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

int DrawGLScene(GLvoid)				// Draw Everything
{
    bool sceneDrawn = FALSE;
    int tick = SDL_GetTicks();
    if ( tick <= gLastTick)
    {
        SDL_Delay(1);
        return TRUE;
    }
    while (gLastTick < tick)
    {
        if ( !sceneDrawn )
        {
            // Clear Screen, Depth Buffer & Stencil Buffer
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Draw our sprites
            glPushMatrix();
            glLoadIdentity();
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            for(int i = 0; i < 4; i++)
                DrawSprite(sprites[i], sprites[i].x, sprites[i].y, false);

            glPopMatrix();
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            glFlush();
            sceneDrawn = TRUE;
        }
        gLastTick += 1000 / PHYSICSFPS;
    }
    return TRUE;					// Everything Went OK
}

void ProcessKeyboard()				// Process Keyboard Results
{
    /*
  if (keys[SDLK_RIGHT])	yrotspeed += 0.08f;	// Right Arrow Pressed (Increase yrotspeed)
  if (keys[SDLK_LEFT])	yrotspeed -= 0.08f;	// Left Arrow Pressed (Decrease yrotspeed)
  if (keys[SDLK_DOWN])	xrotspeed += 0.08f;	// Down Arrow Pressed (Increase xrotspeed)
  if (keys[SDLK_UP])	xrotspeed -= 0.08f;	// Up Arrow Pressed (Decrease xrotspeed)

  if (keys[SDLK_a])	zoom +=0.05f;		// 'A' Key Pressed ... Zoom In
  if (keys[SDLK_z])	zoom -=0.05f;		// 'Z' Key Pressed ... Zoom Out

  if (keys[SDLK_PAGEUP]) height +=0.03f;	// Page Up Key Pressed Move Ball Up
  if (keys[SDLK_PAGEDOWN]) height -=0.03f;	// Page Down Key Pressed Move Ball Down
  */
}

GLvoid KillGLWindow(GLvoid)			// Properly Kill The Window
{
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:			*
 *	title			- Title To Appear At The Top Of The Window	*
 *	width			- Width Of The GL Window Or Fullscreen Mode	*
 *	height			- Height Of The GL Window Or Fullscreen Mode	*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)	*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, BOOL fullscreenflag)
{
  Uint32 flags;
  int size;

  fullscreen=fullscreenflag;	// Set The Global Fullscreen Flag
  flags = SDL_OPENGL;
  if ( fullscreenflag ) {
    flags |= SDL_FULLSCREEN;
  }
  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, bits);
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

    flags |= SDL_OPENGL;

  //SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 1 );
  if ( SDL_SetVideoMode(width, height, bits, flags) == NULL ) {
    return FALSE;
  }
  //SDL_GL_GetAttribute( SDL_GL_STENCIL_SIZE, &size);
  //printf("Got a stencil buffer %d bits deep\n", size);

  SDL_WM_SetCaption(title, "opengl");

  //ReSizeGLScene(width, height);		// Set Up Our Perspective GL Screen

  if (!InitGL())			// Initialize Our Newly Created GL Window
  {
    KillGLWindow();			// Reset The Display
    return FALSE;			// Return FALSE
  }
  return TRUE;				// Success
}

void UpdatePhysics()
{
    for(int i = 0; i < 4; i++)
    {
        sprites[i].x += ((rand()%25)-12);
        sprites[i].y += ((rand()%25)-12);
        if ( sprites[i].x > (240-sprites[i].width) )
        {
            sprites[i].x = 240-sprites[i].width;
        }
        else if ( sprites[i].x < 0 )
        {
            sprites[i].x = 0;
        }
        if ( sprites[i].y > (248-sprites[i].height) )
        {
            sprites[i].y = 248-sprites[i].height;
        }
        else if ( sprites[i].y < 0 )
        {
            sprites[i].y = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    srand((unsigned)time(0));
    BOOL	done=FALSE;			// Bool Variable To Exit Loop
    gLastTick = SDL_GetTicks();

  /* Initialize SDL */
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
    fprintf(stderr, "Couldn't init SDL: %s\n", SDL_GetError());
    return 1;
  }

  // Create Our OpenGL Window
  if (!CreateGLWindow("Ultraviolence Moon Patrol", 240, 248, 32, fullscreen))
  {
    SDL_Quit();
    return 0;				// Quit If Window Was Not Created
  }

    while(!done) {			// Loop That Runs While done=FALSE

            SDL_Event event;
            while ( SDL_PollEvent(&event) ) {
                switch (event.type) {
                case SDL_QUIT:
                    done=TRUE;			// If So done=TRUE
                    break;
                default:
                    break;
                }
            }
            keys = SDL_GetKeyState(NULL);

            UpdatePhysics(); // Temp Function

            // Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
            if ((active && !DrawGLScene()) || keys[SDLK_ESCAPE])// Active? Was There A Quit Received?
                done=TRUE;			// ESC or DrawGLScene Signalled A Quit
            else				// Not Time To Quit, Update Screen
                SDL_GL_SwapBuffers();		// Swap Buffers (Double Buffering)
            ProcessKeyboard();			// Processed Keyboard Presses
    }

    // Shutdown
    KillGLWindow();			// Kill The Window
    SDL_Quit();
    return 0;				// Exit The Program
}
