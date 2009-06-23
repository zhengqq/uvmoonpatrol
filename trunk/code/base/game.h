#ifndef __GAME_H__
#define __GAME_H__

#include <math.h>
#include <stdio.h>
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <SDL/SDL.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "base.h"
#include "font.h"
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
#include "spriteManager.h"

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
    void KillGLWindow(void);
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
    Sprite * guiSprite;
    int playerScore;
    int highScore;
    int currentTime;
    int currentTimeBuffer;
    Car * gameCar;
    Cannon * carCannon; // one cannon!
    std::vector<Missile*> carMissile;
    std::vector<MoonMan*> gameMoonMen;
    std::vector<BloodFountain*> mmFountain;
    std::vector<JetMan*> gameJetMen;
    std::vector<JetFountain*> jmFountain;
    std::vector<Boulder*> gameBoulders;
    Level * gameLevel;
    Font * gameFont;

    SpriteManager * spriteManager;
};

#endif // __GAME_H__
