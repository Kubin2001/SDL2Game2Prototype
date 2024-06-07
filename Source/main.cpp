#include <iostream>
#include "Game.h"
int windowWidth = 1400;
int windowHeight = 800;
long long int framesCounter = 0;
int windowType = 2;

int main(int argv, char* argc[])
{
    bool status = true;
    Game* game = new Game();

    game->Start();

    while (status)
    {
        game->Movement(status);
        game->Events();
        game->Render();

        SDL_Delay(16);
    }

    delete game;
    return 0;
}
