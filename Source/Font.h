#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>


class Font {
private:
    SDL_Rect rectangle{ 0,0,29,29 };
    std::vector<SDL_Rect> sourceRectangles;
    SDL_Texture* texture = nullptr;
    int size = 68;

public:
    Font();

    SDL_Rect* GetRectangle();

    SDL_Texture* GetTexture();

    int GetSize();

    void SetSize(int temp);

    void SetTexture(SDL_Texture* temptex);

    void LoadText(int stepW, int stepH);

    void RenderText(SDL_Renderer* renderer, std::string text, int x, int y, int w, int h, int step);

    ~Font();
};