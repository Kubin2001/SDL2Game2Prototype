#include <iostream>
#include <ctime>
#include <algorithm>
#include <SDL.h>
#include "Map.h"
#include "Colision.h"
//WALL
SDL_Rect* Wall::GetRectangle() {
    return &rectangle;
}

int Wall::GetType() {
    return type;
}

void Wall::SetType(int temp) {
    type = temp;
}

bool Wall::GetErasable() {
    return erasable;
}

void Wall::SetErasable(bool temp) {
    erasable = temp;
}
//WALL

//ROOM
SDL_Rect* Room::GetRectangle(int index) {
    return &floorRectangles[index];
}

std::vector<SDL_Rect> &Room::GetRectangles() {
    return floorRectangles;
}

SDL_Texture* Room::GetTextureFloor() {
    return textureFloor;
}

void Room::SetTextureFloor(SDL_Texture* temptex) {
    textureFloor = temptex;
}

SDL_Texture* Room::GetTextureWall() {
    return textureWall;
}

void Room::SetTextureWall(SDL_Texture* temptex) {
    textureWall = temptex;
}

std::vector<Wall>& Room::GetWalls() {
    return walls;
}

void Room::CreateWalls() {
    Wall tempwall;
    SDL_Rect prevReference;
    for (size_t i = 0; i < floorRectangles.size(); i++) {
        tempwall.GetRectangle()->x = GetRectangle(i)->x; //Lewa
        tempwall.GetRectangle()->y = GetRectangle(i)->y + 50;
        tempwall.GetRectangle()->w = 50;
        tempwall.GetRectangle()->h = GetRectangle(i)->h - 50;
        tempwall.SetType(1);
        walls.push_back(tempwall);
        tempwall.GetRectangle()->x = GetRectangle(i)->x; // Górna
        tempwall.GetRectangle()->y = GetRectangle(i)->y;
        tempwall.GetRectangle()->w = GetRectangle(i)->w;
        tempwall.GetRectangle()->h = 50;
        tempwall.SetType(2);
        walls.push_back(tempwall);
        tempwall.GetRectangle()->x = GetRectangle(i)->x + GetRectangle(i)->w - 50; // Prawa
        tempwall.GetRectangle()->y = GetRectangle(i)->y + 50;
        tempwall.GetRectangle()->w = 50;
        tempwall.GetRectangle()->h = GetRectangle(i)->h - 50;
        tempwall.SetType(3);
        walls.push_back(tempwall);
        tempwall.GetRectangle()->x = GetRectangle(i)->x; // Dolna
        tempwall.GetRectangle()->y = GetRectangle(i)->y + GetRectangle(i)->h;
        tempwall.GetRectangle()->w = GetRectangle(i)->w;
        tempwall.GetRectangle()->h = 50;
        tempwall.SetType(4);
        walls.push_back(tempwall);

        prevReference = *GetRectangle(i);
    }

    SDL_Rect temp1;
    SDL_Rect temp2;
    for (size_t i = 0; i < walls.size(); i++)
    {
        for (size_t j = 0; j < walls.size(); j++)
        {
            if (walls[i].GetType() == 1 && walls[j].GetType() == 3) {
                if(SimpleCollision(*walls[i].GetRectangle(), *walls[j].GetRectangle()) == 1) {
                    walls[i].SetErasable(true);
                    walls[j].SetErasable(true);
                }
            }
            else if(walls[i].GetType() == 2 && walls[j].GetType() == 4)
            {
                if(SimpleCollision(*walls[i].GetRectangle(), *walls[j].GetRectangle()) == 1) {
                    walls[i].SetErasable(true);
                    walls[j].SetErasable(true);
                }
            }
            else if (walls[i].GetType() == 4 && walls[j].GetType() == 2)
            {
                if(SimpleCollision(*walls[i].GetRectangle(), *walls[j].GetRectangle()) == 1) {
                    walls[i].SetErasable(true);
                    walls[j].SetErasable(true);
                }
            }
            else if (walls[i].GetType() == 3 && walls[j].GetType() == 1)
            {
                if (SimpleCollision(*walls[i].GetRectangle(), *walls[j].GetRectangle()) == 1) {
                    walls[i].SetErasable(true);
                    walls[j].SetErasable(true);
                }
            }
        }
        
    }

    for (auto it = walls.begin(); it != walls.end(); ) {
        if (it->GetErasable()) {
            it = walls.erase(it);
        }
        else {
            ++it;
        }
    }
}


void Room::RenderRoom(SDL_Renderer *renderer, SDL_Rect& camRect) {
    SDL_Rect temp;
    for (auto& it : floorRectangles) {
        temp.x = it.x - camRect.x;
        temp.y = it.y - camRect.y;
        temp.w = it.w;
        temp.h = it.h;
        SDL_RenderCopy(renderer, GetTextureFloor(), NULL, &temp);
    }
    for (auto &it: walls){
        SDL_Rect temp;
        temp.x = it.GetRectangle()->x - camRect.x;
        temp.y = it.GetRectangle()->y - camRect.y;
        temp.w = it.GetRectangle()->w;
        temp.h = it.GetRectangle()->h;
        SDL_RenderCopy(renderer, GetTextureWall(), NULL, &temp);
    }
}

void Room::CheckCollision(Player* player) {
    for (auto& it : walls) {
        switch (Collision(*player->GetRectangle(), *it.GetRectangle())) {
            case 1:
                player->SetCollision(0, 1);
                break;
            case 2:
                player->SetCollision(1, 1);
                break;
            case 3:
                player->SetCollision(2, 1);
                break;
            case 4:
                player->SetCollision(3, 1);
                break;
        }
    }

}
//ROOM

Map::Map(SDL_Renderer * renderer) {
    this->renderer = renderer;
}

void Map::Render(SDL_Rect& camRect) {
    currentRoom->RenderRoom(renderer, camRect);
}

void Map::LoadTextures() {
    std::string directory = "Textures/Map";
    LoadMultipleTextures(Textures, directory, renderer);
}

void Map::CreateMap() {
    int random = rand() % 100;
    startingRoom = new Room();
    Rooms.push_back(startingRoom);
    startingRoom->SetTextureFloor(Textures[0].GetTexture());
    startingRoom->SetTextureWall(Textures[1].GetTexture());
    SDL_Rect temprect;
    startingRoom->GetRectangles().push_back(temprect);
    startingRoom->GetRectangle(0)->x = 200;
    startingRoom->GetRectangle(0)->y = 100;
    startingRoom->GetRectangle(0)->w = 1000;
    startingRoom->GetRectangle(0)->h = 600;
    startingRoom->GetRectangles().push_back(temprect);
    startingRoom->GetRectangle(1)->x = 1200;
    startingRoom->GetRectangle(1)->y = 100;
    startingRoom->GetRectangle(1)->w = 1000;
    startingRoom->GetRectangle(1)->h = 600;
    startingRoom->GetRectangles().push_back(temprect);
    startingRoom->GetRectangle(2)->x = 200;
    startingRoom->GetRectangle(2)->y = -550;
    startingRoom->GetRectangle(2)->w = 1000;
    startingRoom->GetRectangle(2)->h = 600;
    startingRoom->CreateWalls();
    currentRoom = startingRoom;
}

void Map::CheckCollision(Player *player) {
    currentRoom->CheckCollision(player);
}

Map::~Map() {
    for (auto& it : Textures) {
        SDL_DestroyTexture(it.GetTexture());
    }
}

