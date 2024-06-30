#include <iostream>
#include <SDL.h>
#include "Minimap.h"
#include "TextureManager.h"

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

void Minimap::LoadTextures(TextureManager * texureManger) {
    texureManger->LoadMultipleTextures("Textures/Interface/Minimap");
    textureTile = texureManger->GetTextureByName("Tile");
    texturePlayer = texureManger->GetTextureByName("Player");
    textureDoor = texureManger->GetTextureByName("Doors");
}

void Minimap::Render() {
    for (auto& it : Tiles) {
        SDL_RenderCopy(renderer, textureTile, NULL, it.GetRectangle());
    }
}

void Minimap::CreateTile(SDL_Rect rect, int CordDiffX, int CordDiffY) {
    TileMinimap temptile;
    temptile.GetRectangle()->x = ((rect.x / 25) + windowWidth/2) + CordDiffX;
    temptile.GetRectangle()->y = ((rect.y / 25) + windowHeight/2) + CordDiffY;
    temptile.GetRectangle()->w = 40;
    temptile.GetRectangle()->h = 24;
    Tiles.push_back(temptile);
}

Minimap::~Minimap() {

}

