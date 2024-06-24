#include <iostream>
#include <SDL.h>
#include "Minimap.h"

extern int windowWidth;
extern int windowHeight;

//Minimap Element
SDL_Rect* MinimapElement::GetRectangle() {
    return &rectangle;
}
//Minimap Element

Minimap::Minimap(SDL_Renderer * renderer) {
    this->renderer = renderer;
}

void Minimap::LoadTextures() {
    LoadMultipleTextures(textures, "Textures/Interface/Minimap", renderer);
    for (auto& it : textures) {
        if (it.GetName() == "Tile") {
            textureTile = it.GetTexture();
        }
        else if (it.GetName() == "Player") {
            texturePlayer = it.GetTexture();
        }
        else if (it.GetName() == "Doors") {
            textureDoor = it.GetTexture();
        }
    }
}

void Minimap::Render() {
    for (auto& it : Tiles) {
        SDL_RenderCopy(renderer, textureTile, NULL, it.GetRectangle());
    }
}

void Minimap::CreateTile(SDL_Rect rect, int CordDiffX, int CordDiffY) {
    TileMinimap temptile;
    temptile.GetRectangle()->x = ((rect.x / 25) + windowHeight/2) + CordDiffX;
    temptile.GetRectangle()->y = ((rect.y / 25) + windowWidth/2) + CordDiffY;
    temptile.GetRectangle()->w = 40;
    temptile.GetRectangle()->h = 24;
    Tiles.push_back(temptile);
}

Minimap::~Minimap() {
    for (auto& it : textures) {
        SDL_DestroyTexture(it.GetTexture());
    }
}

