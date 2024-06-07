#pragma once
#include <iostream>
#include <SDL.h>

extern int windowWidth;
extern int windowHeight;

class Camera
{
    private:
        SDL_Rect rectangle{0,0,windowWidth,windowHeight};
        //SDL_Rect rectangle{0,0,windowWidth/2,windowHeight/2};
        //SDL_Rect rectangle{0,0,(windowWidth - 100),(windowHeight- 100)};

    public:
        Camera();

        SDL_Rect* GetRectangle();

        void UpdatePosition(const SDL_Rect playerRect);

        ~Camera();
};
