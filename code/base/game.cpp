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
                // HUGE HUGE HUGE DEBUG!!!
                if ( gameCar->getX() > 146*32 || gameCar->isCrashed() == TRUE){
                    ShutdownGame();
                    InitGame();
                }
                //
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
    generateSprite("data\\gui.bmp",&guiSprite);
    gameCar = new Car();
    gameLevel = new Level();
    carCannon = 0; // nothing for this yet!
    for(int i = 0; i < 32; i++)
        carMissile[i] = 0;
    for(int i = 0; i < 128; i++){
        gameMoonMen[i] = 0;
        gameJetMen[i] = 0;
        mmFountain[i] = 0;
        jmFountain[i] = 0;
        gameBoulders[i] = 0;
    }
    gameLevel->generateMoonMen(&gameMoonMen[0]);
    gameLevel->generateBoulders(&gameBoulders[0]);
    gameLevel->generateJetMen(&gameJetMen[0],&jmFountain[0]);
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
        if ( gameJetMen[i] != 0){
            delete gameJetMen[i];
        }
        if ( mmFountain[i] != 0){
            delete mmFountain[i];
        }
        if ( jmFountain[i] != 0){
            delete jmFountain[i];
        }
        if ( gameBoulders[i] !=  0){
            delete gameBoulders[i];
        }
    }
    glDeleteTextures( 1, &guiSprite.texture );
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
        if ( jmFountain[i] != 0 ){
            jmFountain[i]->draw();
        }
        if ( gameJetMen[i] != 0){
            gameJetMen[i]->draw();
        }
        if ( mmFountain[i] !=  0){
            mmFountain[i]->draw();
        }
        if ( gameBoulders[i] != 0){
            gameBoulders[i]->draw();
        }
    }

    DrawSprite(guiSprite, 0, 0, FALSE);
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
        // Update the land moon men
        if ( gameMoonMen[i] !=  0){
            gameMoonMen[i]->update(scrollX,gameLevel);
            if (rectCollision(gameCar->getX(),gameCar->getY(),gameCar->width(),gameCar->height()-10, // 10 compensates for bottom of the car
                gameMoonMen[i]->getX(),gameMoonMen[i]->getY(),gameMoonMen[i]->width(),gameMoonMen[i]->height())){
                // kill moon man!
                for(int j = 0; j < 128; j++){
                    if ( mmFountain[j] == 0 ){
                        if ( gameCar->isAirBorne() ){
                            mmFountain[j] = new BloodFountain(gameMoonMen[i]->getX()+3,gameMoonMen[i]->getY()+15, 90, 3.0, 100, 0.05);
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
                delete gameMoonMen[i];
                gameMoonMen[i] = 0;
            }

            else if (carCannon != 0 && (rectCollision(carCannon->getX(),carCannon->getY()-4,carCannon->width(),carCannon->height()+8, // 10 compensates for bottom of the car
                gameMoonMen[i]->getX(),gameMoonMen[i]->getY(),gameMoonMen[i]->width(),gameMoonMen[i]->height()))){
                for(int j = 0; j < 128; j++){
                    if ( mmFountain[j] == 0 ){
                        mmFountain[j] = new BloodFountain(gameMoonMen[i]->getX(),gameMoonMen[i]->getY(), 90, 4.0, 60, 0.1);
                        mmFountain[j]->setPop();
                        break;
                    }
                }
                delete carCannon;
                carCannon = 0;
                delete gameMoonMen[i];
                gameMoonMen[i] = 0;
            }
        }
        if ( gameJetMen[i] !=  0){
            gameJetMen[i]->update(scrollX, jmFountain[i],gameCar->getX(),gameCar->getY());
            if (rectCollision(gameCar->getX()+5,gameCar->getY()+30,gameCar->width()-5,gameCar->height()-30, // only 6 pixels will actually collide
                gameJetMen[i]->getX()+3,gameJetMen[i]->getY()+3,gameJetMen[i]->width()-3,gameJetMen[i]->height()-3)){
                // kill Jet man!
                for(int j = 0; j < 128; j++){
                    if ( mmFountain[j] == 0 ){
                        mmFountain[j] = new BloodFountain(gameJetMen[i]->getX(),gameJetMen[i]->getY(), 270, 2.0, 50, 0.3);
                        mmFountain[j]->setPop();
                        break;
                    }
                }
                gameCar->boostUp();
                delete gameJetMen[i];
                gameJetMen[i] = 0;
                delete jmFountain[i];
                jmFountain[i] = 0;
            }
            else if (carCannon != 0 && (rectCollision(carCannon->getX(),carCannon->getY()-4,carCannon->width(),carCannon->height()+8, // 10 compensates for bottom of the car
                gameJetMen[i]->getX(),gameJetMen[i]->getY(),gameJetMen[i]->width(),gameJetMen[i]->height()))){
                for(int j = 0; j < 128; j++){
                    if ( mmFountain[j] == 0 ){
                        mmFountain[j] = new BloodFountain(gameJetMen[i]->getX(),gameJetMen[i]->getY(), 0, 2.0, 40, 0.1);
                        mmFountain[j]->setPop();
                        break;
                    }
                }
                delete carCannon;
                carCannon = 0;
                delete gameJetMen[i];
                gameJetMen[i] = 0;
                delete jmFountain[i];
                jmFountain[i] = 0;
            }
            // check against missiles!
        }
    }
    // Update our particle fountains
    for(int i = 0; i < 128; i++){
        if ( mmFountain[i] !=  0){
            mmFountain[i]->update(scrollX);
            if ( mmFountain[i]->getLife() <= 0 ){
                delete mmFountain[i];
                mmFountain[i] = 0;
            }
        }
        if ( jmFountain[i] !=  0){
            jmFountain[i]->update(scrollX);
        }
    }
    for(int i = 0; i < 128; i++){
        if ( gameBoulders[i] !=  0){
            gameBoulders[i]->update(scrollX);
            if ( gameBoulders[i]->isActive() ){
                if ( rectCollision(gameCar->getX()+5,gameCar->getY(),gameCar->width()-5,gameCar->height()-10, // 10 compensates for bottom of the car
                        gameBoulders[i]->getX(),gameBoulders[i]->getY()+2,gameBoulders[i]->width(),gameBoulders[i]->height())){
                    gameCar->causeCrash();
                }
                else if (carCannon != 0 && (rectCollision(carCannon->getX(),carCannon->getY()-4,carCannon->width(),carCannon->height()+8, // 10 compensates for bottom of the car
                        gameBoulders[i]->getX(),gameBoulders[i]->getY(),gameBoulders[i]->width(),gameBoulders[i]->height()))){
                    gameBoulders[i]->setExplode(); // sets our boulder to explode!
                    delete carCannon;
                    carCannon = 0;
                }
            }
            else if ( gameBoulders[i]->isDead() ){
                delete gameBoulders[i];
                gameBoulders[i] = 0;
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

void Game::KillGLWindow(void)			// Properly Kill The Window
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
