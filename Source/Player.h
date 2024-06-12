#pragma once
#include <iostream>
#include <SDL.h>
extern int windowWidth;
extern int windowHeight;



class Player
{
    private:
        SDL_Renderer* renderer;
        SDL_Texture * texture = nullptr;
        SDL_Rect rectangle{windowWidth /2,windowHeight/2, 32, 70};
        int moveSpeed = 15;

        bool CollsionSides[4] = { 0, 0, 0, 0 };

    public:
        Player(SDL_Renderer* renderer);

        SDL_Rect* GetRectangle();

        SDL_Texture *GetTexture();

        void SetTexture(SDL_Texture* temptex);

        void SetCollision(int index, bool value);

        void Render(SDL_Rect &camRect);

        void Movement(const Uint8* state);

        ~Player();
};
