#include <stdio.h>
#include "game.h"

int main(int argc, char *argv[])
{
    Game * newGame = new Game();
    newGame->Run();
    return 0;				// Exit The Program
}
