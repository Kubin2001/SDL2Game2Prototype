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



void Room::CreateWalls(SDL_Rect rectangle,char missedWall) {
    Wall tempwall;
    SDL_Rect prevReference;
    if (missedWall != 'l') {
        tempwall.GetRectangle()->x = rectangle.x; //Lewa
        tempwall.GetRectangle()->y = rectangle.y;
        tempwall.GetRectangle()->w = 50;
        tempwall.GetRectangle()->h = rectangle.h;
        tempwall.SetType(1);
        walls.push_back(tempwall);
    }
    if (missedWall != 'u') {
        tempwall.GetRectangle()->x = rectangle.x; // Górna
        tempwall.GetRectangle()->y = rectangle.y;
        tempwall.GetRectangle()->w = rectangle.w;
        tempwall.GetRectangle()->h = 50;
        tempwall.SetType(2);
        walls.push_back(tempwall);
    }
    if (missedWall != 'r') {
        tempwall.GetRectangle()->x = rectangle.x + rectangle.w - 50; // Prawa
        tempwall.GetRectangle()->y = rectangle.y;
        tempwall.GetRectangle()->w = 50;
        tempwall.GetRectangle()->h = rectangle.h;
        tempwall.SetType(3);
        walls.push_back(tempwall);
    }
    if (missedWall != 'd') {
        tempwall.GetRectangle()->x = rectangle.x; // Dolna
        tempwall.GetRectangle()->y = rectangle.y + rectangle.h -50;
        tempwall.GetRectangle()->w = rectangle.w;
        tempwall.GetRectangle()->h = 50;
        tempwall.SetType(4);
        walls.push_back(tempwall);
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

void Room::MoveRectangle(SDL_Rect &rect,char deniedSide) {
    int random = rand() % 4 + 1;
    switch (random)
    {
        case 1:
            if (deniedSide == 'l') {
                rect.x += 950;
                CreateWalls(rect, 'l');
            }
            else
            {
                rect.x -= 950;
                CreateWalls(rect, 'r');
            }
            break;
        case 2:
            if (deniedSide == 'n') {
                rect.y -= 550;
                CreateWalls(rect, 'n');
            }
            else
            {
                rect.y += 550;
                CreateWalls(rect, 'n');
            }
            break;
        case 3:
            if (deniedSide == 'n') {
                rect.x -= 950;
                CreateWalls(rect, 'n');
            }
            else
            {
                rect.x += 950;
                CreateWalls(rect, 'n');
            }
            break;
        case 4:
            if (deniedSide == 'n') {
                rect.y += 550;
                CreateWalls(rect, 'n');
            }
            else
            {
                rect.y -= 550;
                CreateWalls(rect, 'n');
            }
            break;
    }
}

void Room::DeleteWalls() {
    for (size_t i = 0; i < walls.size(); ++i) {
        for (size_t j = 0; j < walls.size(); ++j) {
            if (i != j) {  
                if ((walls[i].GetType() == 1 && walls[j].GetType() == 3) ||
                    (walls[i].GetType() == 2 && walls[j].GetType() == 4)) {
                    if (walls[i].GetRectangle()->x == walls[j].GetRectangle()->x &&
                        walls[i].GetRectangle()->y == walls[j].GetRectangle()->y) {
                        walls[i].SetErasable(true);
                        walls[j].SetErasable(true);
                    }
                }
            }
        }
    }


    for (auto it = walls.begin(); it != walls.end();) {
        if (it->GetErasable()) {
            it = walls.erase(it);
        }
        else {
            it++;
        }
    }
    std::cout << "Remaining walls after deletion:" << std::endl;
    for (auto& wall : walls) {
        if(wall.GetType() == 3 || wall.GetType() == 1)
        std::cout << "Wall: Type = " << wall.GetType()
            << ", x = " << wall.GetRectangle()->x
            << ", y = " << wall.GetRectangle()->y << std::endl;
    }
}

void Map::CreateMap() {
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
    startingRoom->CreateWalls(*startingRoom->GetRectangle(0),'n');
    int random = 0;
    SDL_Rect leftRect = *startingRoom->GetRectangle(0);
    SDL_Rect rightRect = *startingRoom->GetRectangle(0);
    SDL_Rect upperRect = *startingRoom->GetRectangle(0);
    SDL_Rect downRect = *startingRoom->GetRectangle(0);
    bool leftPossible = false;
    bool rightPossible = false;
    bool upperPossible = false;
    bool downPossible = false;
    while (roomMaxCount > 0)
    {
        random = rand() % 10 +1;
        if (startingRoom->roomLeft == nullptr && random == 1) {
            roomMaxCount--;
            if (leftPossible) {
                startingRoom->MoveRectangle(leftRect, 'n');
                startingRoom->GetRectangles().push_back(leftRect);
            }
            else
            {
                leftRect.x -= 950;
                startingRoom->GetRectangles().push_back(leftRect);
                leftPossible = true;
                startingRoom->CreateWalls(startingRoom->GetRectangles().back(), 'n');
            }
        }
        else if (startingRoom->roomUp == nullptr && random == 2) {
            roomMaxCount--;
            if (upperPossible) {
                startingRoom->MoveRectangle(upperRect, 'n');
                startingRoom->GetRectangles().push_back(upperRect);
            }
            else
            {
                upperRect.y -= 550;
                startingRoom->GetRectangles().push_back(upperRect);
                upperPossible = true;
                startingRoom->CreateWalls(startingRoom->GetRectangles().back(), 'n');
            }
        }
        else if (startingRoom->roomRight == nullptr && random == 3) {
            roomMaxCount--;
            if (rightPossible) {
                startingRoom->MoveRectangle(rightRect, 'n');
                startingRoom->GetRectangles().push_back(rightRect);
            }
            else
            {
                rightRect.x += 950;
                startingRoom->GetRectangles().push_back(rightRect);
                rightPossible = true;
                startingRoom->CreateWalls(startingRoom->GetRectangles().back(), 'n');
            }
        }
        else if (startingRoom->roomDown == nullptr && random == 4) {
            roomMaxCount--;
            if (downPossible) {
                startingRoom->MoveRectangle(downRect, 'n');
                startingRoom->GetRectangles().push_back(downRect);
            }
            else
            {
                downRect.y += 550;
                startingRoom->GetRectangles().push_back(downRect);
                downPossible = true;
                startingRoom->CreateWalls(startingRoom->GetRectangles().back(), 'n');
            }
        }
    }
    startingRoom->DeleteWalls();
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


/*if (startingRoom->roomLeft == nullptr && random == 1) {
    roomMaxCount--;
    MoveRectangle(leftRect, 'r');
    startingRoom->GetRectangles().push_back(leftRect);
}
else if (startingRoom->roomUp == nullptr && random == 2) {
    roomMaxCount--;
    MoveRectangle(upperRect, 'd');
    startingRoom->GetRectangles().push_back(upperRect);
}
else if (startingRoom->roomRight == nullptr && random == 3) {
    roomMaxCount--;
    MoveRectangle(rightRect, 'l');
    startingRoom->GetRectangles().push_back(rightRect);
}
else if (startingRoom->roomDown == nullptr && random == 4) {
    roomMaxCount--;
    MoveRectangle(downRect, 'u');
    startingRoom->GetRectangles().push_back(downRect);
}*/


/*if (startingRoom->roomLeft == nullptr && random == 1) {
    roomMaxCount--;
    leftRect.x -= 950;
    startingRoom->GetRectangles().push_back(leftRect);
}
else if (startingRoom->roomUp == nullptr && random == 2) {
    roomMaxCount--;
    upperRect.y -= 600;
    startingRoom->GetRectangles().push_back(upperRect);
}
else if (startingRoom->roomRight == nullptr && random == 3) {
    roomMaxCount--;
    rightRect.x += 950;
    startingRoom->GetRectangles().push_back(rightRect);
}
else if (startingRoom->roomDown == nullptr && random == 4) {
    roomMaxCount--;
    downRect.y += 600;
    startingRoom->GetRectangles().push_back(downRect);
}*/