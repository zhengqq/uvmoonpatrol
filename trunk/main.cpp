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
#define KEY_R 0
#define KEY_G 255
#define KEY_B 0
// Physics iterations per second
#define PHYSICSFPS 30

int         gLastTick;
Uint8*		keys;			// Array Used For The Keyboard Routine
BOOL		active=TRUE;		// Window Active Flag Set To TRUE By Default
BOOL		fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

int gTextureCount = 12; // how many textures we have
char * gTextureList[12] = {"data\\bus1_1.bmp","data\\bus1_2.bmp","data\\car.bmp",
                    "data\\flyingman.bmp","data\\running1_1.bmp","data\\running1_2.bmp",
                    "data\\wheel1_1.bmp","data\\wheel1_2.bmp","data\\wheel2_1.bmp",
                    "data\\wheel2_2.bmp","data\\wheel3_1.bmp","data\\wheel3_2.bmp"};

struct Sprite
{
	GLuint texture;
	char * name;
	int width;
	int height;
	int x;
	int y;
};

Sprite		sprites[12];

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
    for(int i = 0; i < (image->w*image->h);i++)
    {
        unsigned char * R = pixelPtr;
        unsigned char * G = R + sizeof(unsigned char);
        unsigned char * B = G + sizeof(unsigned char);
        // Lets start dumping them into our new memory!
        * newPixelPtr++ = *B;
        * newPixelPtr++ = *G;
        * newPixelPtr++ = *R;
        if ( *B == KEY_B && *G == KEY_G && *R == KEY_R )
        {
            * newPixelPtr++ = 0;
        }
        else
        {
            * newPixelPtr++ = 255;
        }
        pixelPtr += sizeof(unsigned char)*3;
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

int LoadGLTextures() 		// Load Bitmaps And Convert To Textures
{
    int noError=TRUE;		// Status Indicator
    SDL_Surface *TextureImage[gTextureCount];	// Create Storage Space For The Textures
    memset(TextureImage,0,sizeof(void *)*gTextureCount);	// Set The Pointer To NULL
    for(int i = 0; i < gTextureCount; i++)
    {
        TextureImage[i]=LoadBMP2RGBA(gTextureList[i]);
        if (TextureImage[i]==NULL)
        {
            printf("Error, could not load textures!\n");
            noError=FALSE;
            break;
        }
        glGenTextures(1, &sprites[i].texture);		// Create The Texture
        glBindTexture(GL_TEXTURE_2D, sprites[i].texture);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TextureImage[i]->w, TextureImage[i]->h, GL_RGBA, GL_UNSIGNED_BYTE, TextureImage[i]->pixels);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureImage[loop]->w, TextureImage[loop]->h,
        //    0, GL_RGBA, GL_UNSIGNED_BYTE, TextureImage[loop]->pixels);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        sprites[i].width = TextureImage[i]->w;
        sprites[i].height = TextureImage[i]->h;
        sprites[i].x = sprites[i].y = 0; // ### DEBUG! ###
        sprites[i].name = gTextureList[i];
        if (TextureImage[i]) {		// If Texture Exists
            SDL_FreeSurface(TextureImage[i]);
        }
    }
    return noError;
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
            for(int i = 0; i < gTextureCount; i++)
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
    SDL_ShowCursor(FALSE); // hide our cursor

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
    // We have all the sprite names, but we are going to cheat here
    sprites[2].x = 50;
    sprites[2].y = 100;
    sprites[6].x = 45;
    sprites[6].y = 100;
    sprites[8].x = 60;
    sprites[8].y = 100;
    sprites[10].x = 75;
    sprites[10].y = 100;
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
