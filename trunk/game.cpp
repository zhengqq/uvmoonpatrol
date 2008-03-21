#include "game.h"

Game::Game(){
}

Game::~Game(){
    Shutdown();
    if ( currentScene == INTRO){
    }
    else if ( currentScene == SPLASH ){
    }
    else if ( currentScene == INGAME ){
        ShutdownGame();
    }
}

int Game::Init(){
    srand((unsigned)time(0));
    gLastTick = SDL_GetTicks();

    gKeyLeft=gKeyRight=gKeyUp=gKeyDown=gKeySpace=gKeyCtrl=done=FALSE;
    fullscreen=FALSE;

    /* Initialize SDL */
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Couldn't init SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Create Our OpenGL Window
    if (!CreateGLWindow("Ultraviolent Moon Patrol", SCREEN_WIDTH, SCREEN_HEIGHT, 32, fullscreen))
    {
        SDL_Quit();
        return 0;				// Quit If Window Was Not Created
    }

    if (!InitGL())			// Initialize Our Newly Created GL Window
    {
        KillGLWindow();			// Reset The Display
        return -1;			// Return Error
    }
    return 1;
}

void Game::Shutdown(){
    // Shutdown
    KillGLWindow();			// Kill The Window
    SDL_Quit();
}

void Game::Run(){
    if ( Init() )
    {
        currentScene = INGAME;
        InitGame();
        while(!done) {
            if ( currentScene == INTRO ){
                IntroLogic();
                IntroRender();
            }
            else if ( currentScene == SPLASH ){
            }
            else if ( currentScene == INGAME ){
                GameLogic();
                GameRender();
            }
            Timer();
        }
    }
}

void Game::InitIntro()
{
}

void Game::ShutdownIntro()
{
}

void Game::IntroRender()
{
}

void Game::IntroLogic()
{
    KeyInput();
}

void Game::InitGame()
{
    gameCar = new Car();
    gameLevel = new Level();
    carCannon = 0; // nothing for this yet!
    for(int i = 0; i < 32; i++)
        carMissile[i] = 0;
    for(int i = 0; i < 128; i++){
        gameMoonMen[i] = 0;
        mmFountain[i] = 0;
    }
    gameLevel->generateMoonMen(&gameMoonMen[0]);
}

void Game::ShutdownGame()
{
    delete gameCar;
    delete gameLevel;
    if ( carCannon != 0 ){
        delete carCannon;
    }
    for(int i = 0; i < 32; i++){
        if ( carMissile[i] != 0){
            delete carMissile[i];
        }
    }
    for(int i = 0; i < 128; i++){
        if ( gameMoonMen[i] != 0){
            delete gameMoonMen[i];
        }
        if ( mmFountain[i] != 0){
            delete mmFountain[i];
        }
    }
}

void Game::GameRender()				// Draw Everything
{
    // Clear Screen, Depth Buffer & Stencil Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw our sprites
    glPushMatrix();
    glLoadIdentity();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    gameLevel->draw();
    gameCar->draw();
    if ( carCannon != 0 ){
        carCannon->draw();
    }
    for(int i = 0; i < 32; i++){
        if ( carMissile[i] != 0){
            carMissile[i]->draw();
        }
    }
    for(int i = 0; i < 128; i++){
        if ( gameMoonMen[i] !=  0){
            gameMoonMen[i]->draw();
        }
        if ( mmFountain[i] !=  0){
            mmFountain[i]->draw();
        }
    }

    glPopMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glFlush();

    SDL_GL_SwapBuffers();
}

void Game::GameLogic()
{
    KeyInput();

    if (gKeyLeft)
        gameCar->moveLeft();
    else if (gKeyRight)
        gameCar->moveRight();
    else
        gameCar->stopMove();
    if (gKeySpace)
        gameCar->jump();
    if (gKeyCtrl){
        if ( carCannon == 0){
            carCannon = new Cannon(gameCar->getX()+32,gameCar->getY()+16);
        }
        for(int i = 0; i < 32; i++){
            if ( carMissile[i] == 0 ){
                carMissile[i] = new Missile(gameCar->getX()-gameCar->getScreenX()+9,gameCar->getY()+5);
                gKeyCtrl = FALSE; // hacky way of doing this.
                break;
            }
        }
    }
    //if (gKeyUp) gKeyUp=gKeyUp;
    //if (gKeyDown) gKeyDown=gKeyDown;

/*
    if (rectCollision(mainCar->getX(),mainCar->getY(),mainCar->width(),mainCar->height(), \
           mainMan[i]->getX(),mainMan[i]->getY(),mainMan[i]->width(),mainMan[i]->height())){*/

    gameCar->update(gameLevel);
    int scrollX = gameCar->getScreenX();
    gameLevel->update(scrollX);

    if ( carCannon!= 0){
        if ( carCannon->getLife() <= 0 ){
            delete carCannon;
            carCannon = 0;
        }
        else{
            carCannon->update(scrollX);
        }
    }
    for(int i = 0; i < 32; i++){
        if ( carMissile[i] != 0){
            if ( carMissile[i]->getY() < 10 ){
                delete carMissile[i];
                carMissile[i] = 0;
            }
            else {
                carMissile[i]->update();
            }
        }
    }
    for(int i = 0; i < 128; i++){
        if ( gameMoonMen[i] !=  0){
            gameMoonMen[i]->update(scrollX,gameLevel);
            if ( !gameMoonMen[i]->isDead() ){
                if (rectCollision(gameCar->getX(),gameCar->getY(),gameCar->width(),gameCar->height()-10, // 10 compensates for bottom of the car
                    gameMoonMen[i]->getX(),gameMoonMen[i]->getY(),gameMoonMen[i]->width(),gameMoonMen[i]->height())){
                    // kill moon man!
                    gameMoonMen[i]->kill();
                    for(int j = 0; j < 128; j++){
                        if ( mmFountain[j] == 0 ){
                            if ( gameCar->isAirBorne() ){
                                mmFountain[j] = new BloodFountain(gameMoonMen[i]->getX()+3,gameMoonMen[i]->getY()+5, 90, 3.0, 100, 0.05);
                                mmFountain[j]->setSpurting();
                            }
                            else{
                                mmFountain[j] = new BloodFountain(gameMoonMen[i]->getX(),gameMoonMen[i]->getY(), 90, 2.0, 50, 0.01);
                                mmFountain[j]->setPop();
                            }
                            break;
                        }
                    }
                    if ( gameCar->isAirBorne() ){
                        gameCar->boostUp();
                    }
                    else{
                        gameCar->slowDown();
                    }
                }

                else if (carCannon != 0 && (rectCollision(carCannon->getX(),carCannon->getY()-4,carCannon->width(),carCannon->height(), // 10 compensates for bottom of the car
                    gameMoonMen[i]->getX(),gameMoonMen[i]->getY(),gameMoonMen[i]->width(),gameMoonMen[i]->height()))){
                    gameMoonMen[i]->kill();
                    for(int j = 0; j < 128; j++){
                        if ( mmFountain[j] == 0 ){
                            mmFountain[j] = new BloodFountain(gameMoonMen[i]->getX(),gameMoonMen[i]->getY(), 90, 4.0, 60, 0.1);
                            mmFountain[j]->setPop();
                            break;
                        }
                    }
                    delete carCannon;
                    carCannon = 0;
                }
            }
        }
    }
    for(int i = 0; i < 128; i++){
        if ( mmFountain[i] !=  0){
            mmFountain[i]->update(scrollX);
            if ( mmFountain[i]->getLife() <= 0 ){
                delete mmFountain[i];
                mmFountain[i] = 0;
            }
        }
    }
}

void Game::KeyInput()
{
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
                case SDLK_SPACE:
                    gKeySpace=TRUE;
                break;
                case SDLK_LCTRL:
                    gKeyCtrl=TRUE;
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
                case SDLK_SPACE:
                    gKeySpace=FALSE;
                break;
                case SDLK_LCTRL:
                    gKeyCtrl=FALSE;
                break;
                default:
                break;
            }
        }
    }
}

void Game::Timer()
{
    if((SDL_GetTicks() - startTime) < 1000.0/PHYSICSFPS)
        SDL_Delay(int(1000.0/PHYSICSFPS - (SDL_GetTicks() - startTime)));

    startTime = SDL_GetTicks();
}

GLvoid Game::KillGLWindow(GLvoid)			// Properly Kill The Window
{
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:			*
 *	title			- Title To Appear At The Top Of The Window	*
 *	width			- Width Of The GL Window Or Fullscreen Mode	*
 *	height			- Height Of The GL Window Or Fullscreen Mode	*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)	*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL Game::CreateGLWindow(char* title, int width, int height, int bits, BOOL fullscreenflag)
{
  Uint32 flags;
  int size;

  fullscreen=fullscreenflag;	// Set The Global Fullscreen Flag
  flags = SDL_OPENGL;
  if ( fullscreenflag ) {
    flags |= SDL_FULLSCREEN;
  }
  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, bits);
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

  //SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 1 );
  if ( SDL_SetVideoMode(width, height, bits, flags) == NULL ) {
    return FALSE;
  }

  SDL_WM_SetCaption(title, "opengl");
    SDL_ShowCursor(FALSE); // hide our cursor

  //ReSizeGLScene(width, height);		// Set Up Our Perspective GL Screen
  return TRUE;				// Success
}
