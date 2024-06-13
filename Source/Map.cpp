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


//FLOOR
SDL_Rect* Floor::GetRectangle() {
    return &rectangle;
}

bool Floor::GetErasable() {
    return erasable;
}

void Floor::SetErasable(bool temp) {
    erasable = temp;
}
//FLOOR

//ROOM

std::vector<Floor> &Room::GetFloors() {
    return Floors;
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
    for (auto& it : GetFloors()) {
        SDL_Rect prevReference;
        tempwall.GetRectangle()->x = it.GetRectangle()->x; //Lewa
        tempwall.GetRectangle()->y = it.GetRectangle()->y;
        tempwall.GetRectangle()->w = 50;
        tempwall.GetRectangle()->h = it.GetRectangle()->h;
        tempwall.SetType(1);
        walls.push_back(tempwall);

        tempwall.GetRectangle()->x = it.GetRectangle()->x; // Górna
        tempwall.GetRectangle()->y = it.GetRectangle()->y;
        tempwall.GetRectangle()->w = it.GetRectangle()->w;
        tempwall.GetRectangle()->h = 50;
        tempwall.SetType(2);
        walls.push_back(tempwall);

        tempwall.GetRectangle()->x = it.GetRectangle()->x + it.GetRectangle()->w - 50; // Prawa
        tempwall.GetRectangle()->y = it.GetRectangle()->y;
        tempwall.GetRectangle()->w = 50;
        tempwall.GetRectangle()->h = it.GetRectangle()->h;
        tempwall.SetType(3);
        walls.push_back(tempwall);

        tempwall.GetRectangle()->x = it.GetRectangle()->x; // Dolna
        tempwall.GetRectangle()->y = it.GetRectangle()->y + it.GetRectangle()->h - 50;
        tempwall.GetRectangle()->w = it.GetRectangle()->w;
        tempwall.GetRectangle()->h = 50;
        tempwall.SetType(4);
        walls.push_back(tempwall);
    }
}


void Room::RenderRoom(SDL_Renderer *renderer, SDL_Rect& camRect) {
    SDL_Rect temp;
    for (auto& it : GetFloors()) {
        temp.x = it.GetRectangle()->x - camRect.x;
        temp.y = it.GetRectangle()->y - camRect.y;
        temp.w = it.GetRectangle()->w;
        temp.h = it.GetRectangle()->h;
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

void Room::MoveRectangle(Floor &floor,char deniedSide) {
    int random = rand() % 4 + 1;
    switch (random)
    {
        case 1:
            if (deniedSide == 'l') {
                floor.GetRectangle()->x += 950;
            }
            else
            {
                floor.GetRectangle()->x -= 950;
            }
            break;
        case 2:
            if (deniedSide == 'u') {
                floor.GetRectangle()->y -= 550;
            }
            else
            {
                floor.GetRectangle()->y += 550;
            }
            break;
        case 3:
            if (deniedSide == 'r') {
                floor.GetRectangle()->x -= 950;
            }
            else
            {
                floor.GetRectangle()->x += 950;
            }
            break;
        case 4:
            if (deniedSide == 'd') {
                floor.GetRectangle()->y += 550;
            }
            else
            {
                floor.GetRectangle()->y -= 550;
            }
            break;
    }
}

void Room::DeleteRectangles() {
    int size = 0;
    for (size_t i = 0; i < GetFloors().size(); ++i) {
        for (size_t j = i; j < GetFloors().size(); ++j) {
            if (i != j) {
                if (GetFloors()[i].GetRectangle()->x == GetFloors()[j].GetRectangle()->x &&
                    GetFloors()[i].GetRectangle()->y == GetFloors()[j].GetRectangle()->y) {
                    GetFloors()[j].SetErasable(true);
                    size++;
                }
            }
        }
    }

    std::cout << "SIZE: "<< size << "\n";

    for (auto it = GetFloors().begin(); it != GetFloors().end();) {
        if (it->GetErasable()) {
            it = GetFloors().erase(it);
        }
        else {
            it++;
        }
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

    Floor tempFloor;
    startingRoom->GetFloors().push_back(tempFloor);
    startingRoom->GetFloors().back().GetRectangle()->x = 200;
    startingRoom->GetFloors().back().GetRectangle()->y = 100;
    startingRoom->GetFloors().back().GetRectangle()->w = 1000;
    startingRoom->GetFloors().back().GetRectangle()->h = 600;
    int random = 0;
    Floor leftRect = startingRoom->GetFloors().back();
    Floor rightRect = startingRoom->GetFloors().back();
    Floor upperRect = startingRoom->GetFloors().back();
    Floor downRect = startingRoom->GetFloors().back();
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
                startingRoom->MoveRectangle(leftRect, 'r');
                startingRoom->GetFloors().push_back(leftRect);
            }
            else
            {
                leftRect.GetRectangle()->x -= 950;
                startingRoom->GetFloors().push_back(leftRect);
                leftPossible = true;
            }
        }
        else if (startingRoom->roomUp == nullptr && random == 2) {
            roomMaxCount--;
            if (upperPossible) {
                startingRoom->MoveRectangle(upperRect, 'd');
                startingRoom->GetFloors().push_back(upperRect);
            }
            else
            {
                upperRect.GetRectangle()->y -= 550;
                startingRoom->GetFloors().push_back(upperRect);
                upperPossible = true;
            }
        }
        else if (startingRoom->roomRight == nullptr && random == 3) {
            roomMaxCount--;
            if (rightPossible) {
                startingRoom->MoveRectangle(rightRect, 'l');
                startingRoom->GetFloors().push_back(rightRect);
            }
            else
            {
                rightRect.GetRectangle()->x += 950;
                startingRoom->GetFloors().push_back(rightRect);
                rightPossible = true;
            }
        }
        else if (startingRoom->roomDown == nullptr && random == 4) {
            roomMaxCount--;
            if (downPossible) {
                startingRoom->MoveRectangle(downRect, 'u');
                startingRoom->GetFloors().push_back(downRect);
            }
            else
            {
                downRect.GetRectangle()->y += 550;
                startingRoom->GetFloors().push_back(downRect);
                downPossible = true;
            }
        }
    }
    startingRoom->CreateWalls();
    startingRoom->DeleteRectangles();
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