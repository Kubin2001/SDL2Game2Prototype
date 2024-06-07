#pragma once
#include <iostream>
#include <SDL.h>
#include "SDL_mixer.h"



class SoundManager
{
    private:


    public:
        SoundManager();

        static void LoadMenu();

        static void LoadGame();

        static void LoadEditor();

        static void UnLoadMenu();

        static void UnLoadGame();

        static void UnLoadEditor();

        ~SoundManager();
};
