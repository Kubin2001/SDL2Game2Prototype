#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include "TextureManager.h"
#include "Player.h"

class Wall {
    private:
        SDL_Rect rectangle;
        int type = 0;
        bool erasable = false;

    public:
        int GetType();
        void SetType(int temp);

        bool GetErasable();
        void SetErasable(bool temp);
        SDL_Rect* GetRectangle();

};

class Room {
    private:
        std::vector<SDL_Rect> floorRectangles;
        SDL_Texture* textureFloor;
        SDL_Texture* textureWall;
        std::vector<Wall> walls;
        int size = 1;

    public:
        Room* roomLeft = nullptr;
        Room* roomRight = nullptr;
        Room* roomUp = nullptr;
        Room* roomDown = nullptr;

        SDL_Rect* GetRectangle(int index);

        std::vector<SDL_Rect> &GetRectangles();

        SDL_Texture* GetTextureFloor();

        void SetTextureFloor(SDL_Texture* temptex);

        SDL_Texture* GetTextureWall();

        void SetTextureWall(SDL_Texture* temptex);

        std::vector<Wall> &GetWalls();

        void CreateWalls();

        void RenderRoom(SDL_Renderer* renderer, SDL_Rect& camRect);

        void CheckCollision(Player * player);
};


class Map
{
    private:
        SDL_Renderer* renderer;
        std::vector<Texture> Textures;
        Room* startingRoom = nullptr;
        std::vector<Room*> Rooms;
        Room* currentRoom = nullptr;

        int roomCount = 20;

    public:
        Map(SDL_Renderer* renderer);

        SDL_Texture *GetTexture();

        void SetTexture(SDL_Texture* temptex);

        void Render(SDL_Rect& camRect);

        void LoadTextures();

        void CreateMap();

        void CheckCollision(Player* player);

        ~Map();
};
