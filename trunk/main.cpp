#include <math.h>
#include <stdio.h>
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <SDL/SDL.h>
#include <cstdlib>
#include <ctime>
#include "base.h"
#include "gfx.h"
#include "car.h"

int         gLastFrame;
int         gLastTick;
BOOL		active=TRUE;		// Window Active Flag Set To TRUE By Default
BOOL		fullscreen=FALSE;	// Fullscreen Flag Set To Fullscreen Mode By Default
BOOL        gKeyLeft,gKeyRight,gKeyUp,gKeyDown;

Car*        mainCar;

int InitGL(GLvoid)			// All Setup For OpenGL Goes Here
{
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

int DrawGLScene(GLvoid)				// Draw Everything
{
    int tick = SDL_GetTicks();
    if (tick <= gLastFrame && (((1000/PHYSICSFPS)-(tick-gLastTick)>0)))
    {
        SDL_Delay((1000 / PHYSICSFPS) - (tick-gLastTick));
        return TRUE;
    }
    gLastTick = tick;
    while (gLastFrame < tick)
    {
        if (gKeyLeft) mainCar->moveLeft();
        if (gKeyRight) mainCar->moveRight();
        if (gKeyUp) gKeyUp=gKeyUp;
        if (gKeyDown) gKeyDown=gKeyDown;

        // Physics updates go here!

        gLastFrame += 1000 / PHYSICSFPS;
    }

    // Clear Screen, Depth Buffer & Stencil Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw our sprites
    glPushMatrix();
    glLoadIdentity();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    mainCar->draw();

    glPopMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glFlush();

    return TRUE;					// Everything Went OK
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
  flags = SDL_OPENGL | SDL_HWSURFACE;
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
  return TRUE;				// Success
}

int main(int argc, char *argv[])
{
    srand((unsigned)time(0));
    BOOL	done=FALSE;			// Bool Variable To Exit Loop
    gLastTick = SDL_GetTicks();

    gKeyLeft=gKeyRight=gKeyUp=gKeyDown=FALSE;

    /* Initialize SDL */
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Couldn't init SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Create Our OpenGL Window
    if (!CreateGLWindow("Ultraviolence Moon Patrol", SCREEN_WIDTH, SCREEN_HEIGHT, 32, fullscreen))
    {
        SDL_Quit();
        return 0;				// Quit If Window Was Not Created
    }

    // Call our car here!
    mainCar = new Car();

    if (!InitGL())			// Initialize Our Newly Created GL Window
    {
        KillGLWindow();			// Reset The Display
        return -1;			// Return Error
    }

    while(!done) {			// Loop That Runs While done=FALSE

            // Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
            if ((active && !DrawGLScene()))// Active? Was There A Quit Received?
                done=TRUE;			// ESC or DrawGLScene Signalled A Quit
            else				// Not Time To Quit, Update Screen
                SDL_GL_SwapBuffers();		// Swap Buffers (Double Buffering)

            SDL_Event event;
            while ( SDL_PollEvent(&event) ) {
                switch (event.type) {
                case SDL_QUIT:
                    done=TRUE;			// If So done=TRUE
                    break;
                default:
                    break;
                }

                if (event.type == SDL_KEYDOWN)
                {
                    switch(event.key.keysym.sym){
                        case SDLK_LEFT:
                            gKeyLeft=TRUE;
                        break;
                        case SDLK_RIGHT:
                            gKeyRight=TRUE;
                        break;
                        case SDLK_UP:
                            gKeyUp=TRUE;
                        break;
                        case SDLK_DOWN:
                            gKeyDown=TRUE;
                        break;
                        case SDLK_ESCAPE:
                            done=TRUE;
                        break;
                        default:

                        break;
                    }
                }
                if (event.type == SDL_KEYUP)
                {
                    switch(event.key.keysym.sym){
                        case SDLK_LEFT:
                            gKeyLeft=FALSE;
                        break;
                        case SDLK_RIGHT:
                            gKeyRight=FALSE;
                        break;
                        case SDLK_UP:
                            gKeyUp=FALSE;
                        break;
                        case SDLK_DOWN:
                            gKeyDown=FALSE;
                        break;
                        default:
                        break;
                    }
                }
            }
    }

    // Shutdown
    KillGLWindow();			// Kill The Window
    SDL_Quit();

    delete mainCar;

    return 0;				// Exit The Program
}
