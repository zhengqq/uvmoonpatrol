#ifndef __GAME_H__
#define __GAME_H__

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
#include "level.h"
#include "moonman.h"
#include "cannon.h"
#include "missile.h"
#include "bloodfountain.h"
#include "jetfountain.h"
#include "jetman.h"
#include "boulder.h"

typedef enum {
    INTRO=0,
    SPLASH,
    INGAME
};

class Game
{
public:
    Game();
    ~Game();
    void Run();
private:
    int Init();
    void Shutdown();
    void KeyInput();
    void Timer();
    BOOL CreateGLWindow(char* title, int width, int height, int bits, BOOL fullscreenflag);
    GLvoid KillGLWindow(GLvoid);
    unsigned int currentScene;
    int         gLastFrame;
    int         gLastTick;
    int         startTime;
    BOOL    	done;			// Bool Variable To Exit Loop
    BOOL		fullscreen;	// Fullscreen Flag Set To Fullscreen Mode By Default
    BOOL        gKeyLeft,gKeyRight,gKeyUp,gKeyDown,gKeySpace,gKeyCtrl;
    // INTRO variables
    void InitIntro();
    void ShutdownIntro();
    void IntroRender();
    void IntroLogic();

    // GAME functions & variables
    void InitGame();
    void ShutdownGame();
    void GameRender();
    void GameLogic();
    Sprite guiSprite;
    Car * gameCar;
    Cannon * carCannon; // one cannon!
    Missile * carMissile[32]; // up to 32 missiles!
    MoonMan * gameMoonMen[128]; // 128 moon men (THIS IS A DEBUG, WE MIGHT MAKE THIS DYNAMIC!)
    BloodFountain * mmFountain[128]; // 128 blood fountains to correspond with our 128 moon men
    JetMan * gameJetMen[128];
    JetFountain * jmFountain[128];
    Boulder * gameBoulders[128];
    Level * gameLevel;
};

#endif // __GAME_H__
