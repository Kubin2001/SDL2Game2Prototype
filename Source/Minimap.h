#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include "TextureManager.h"

class MinimapElement {
    private:
        SDL_Rect rectangle;

    public:
        SDL_Rect* GetRectangle();
};

class PlayerMinimap : public MinimapElement{
    public:

    private:

};

class DoorMinimap : public MinimapElement {
    public:

    private:

};

class TileMinimap : public MinimapElement {
    public:

    private:

};

class Minimap
{
    private:
        SDL_Renderer* renderer;
        SDL_Texture * texturePlayer = nullptr;
        SDL_Texture* textureTile = nullptr;
        SDL_Texture* textureDoor = nullptr;
        PlayerMinimap playerMinimap;
        std::vector<DoorMinimap> Doors;
        std::vector<TileMinimap> Tiles;

    public:
        
        Minimap(SDL_Renderer* renderer);

        void LoadTextures(TextureManager* texureManger);

        void Render();

        void CreateTile(SDL_Rect rect, int CordDiffX, int CordDiffY);

        ~Minimap();
};
