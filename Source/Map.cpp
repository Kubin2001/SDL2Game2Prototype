#include <iostream>
#include <ctime>
#include <algorithm>
#include <SDL.h>
#include "Map.h"
#include "Colision.h"
//DOOR
SDL_Rect* Door::GetRectangle() {
    return &rectangle;
}
int Door::GetType() {
    return type;
}

void Door::SetType(int temp) {
    type = temp;
}

//DOOR
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


std::vector<Door>& Room::GetDoors() {
    return Doors;
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

SDL_Texture* Room::GetTextureDoor() {
    return textureDoor;
}

void Room::SetTextureDoor(SDL_Texture* temptex) {
    textureDoor = temptex;
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
    for (auto& it : Doors) {
        SDL_Rect temp;
        temp.x = it.GetRectangle()->x - camRect.x;
        temp.y = it.GetRectangle()->y - camRect.y;
        temp.w = it.GetRectangle()->w;
        temp.h = it.GetRectangle()->h;
        SDL_RenderCopy(renderer, GetTextureDoor(), NULL, &temp);
    }
}

void Room::CheckCollision(Player* player) {
    for (auto& it : walls) {
        switch (AdvancedCollision(*player->GetRectangle(), *it.GetRectangle(),18)) {
            case 1:
                if (it.GetType() == 1 || it.GetType() == 3) {
                    player->SetCollision(0, 1);
                }
                break;
            case 2:
                if (it.GetType() == 2 || it.GetType() == 4) {
                    player->SetCollision(1, 1);
                }
                break;
            case 3:
                if (it.GetType() == 1 || it.GetType() == 3) {
                    player->SetCollision(2, 1);
                }
                break;
            case 4:
                if (it.GetType() == 2 || it.GetType() == 4) {
                    player->SetCollision(3, 1);
                }
                break;
        }
    }
}

int Room::CheckCollisionDoors(Player* player) {
    for (auto& it : Doors) {
        if (SimpleCollision(*player->GetRectangle(), *it.GetRectangle())) {
            switch (it.GetType()) {
                case 1:
                    return 1;
                    break;
                case 2:
                    return 2;
                    break;
                case 3:
                    return 3;
                    break;
                case 4:
                    return 4;
                    break;
            }
        }
    }
    return 0;
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
    for (auto &it :Textures)
    {
        std::cout << it.GetName() << "\n";
    }
}

void Room::MoveRectangle(Floor &floor,char deniedSide) {
    int random = rand() % 4 + 1;
    switch (random)
    {
        case 1:
            if (deniedSide == 'l') {floor.GetRectangle()->x += 950; }

            else{floor.GetRectangle()->x -= 950; }
            break;
        case 2:
            if (deniedSide == 'u') {floor.GetRectangle()->y -= 550; }

            else{floor.GetRectangle()->y += 550; }
            break;
        case 3:
            if (deniedSide == 'r') {floor.GetRectangle()->x -= 950; }

            else{floor.GetRectangle()->x += 950; }
            break;
        case 4:
            if (deniedSide == 'd') {floor.GetRectangle()->y += 550; }

            else{floor.GetRectangle()->y -= 550; }
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
}

void Room::LocateDoorPositions() {
    Door door;
    Doors.push_back(door);
    Doors.push_back(door);
    Doors.push_back(door);
    Doors.push_back(door);
    
    if (roomLeft != nullptr) {
        Doors[0].GetRectangle()->x = 2000;
        Doors[0].GetRectangle()->y = 0;
        Doors[0].GetRectangle()->w = 50;
        Doors[0].GetRectangle()->h = 50;
        Doors[0].SetType(1);
    }
    if (roomRight != nullptr) {
        Doors[2].GetRectangle()->x = -2000;
        Doors[2].GetRectangle()->y = 0;
        Doors[2].GetRectangle()->w = 50;
        Doors[2].GetRectangle()->h = 50;
        Doors[2].SetType(3);
    }
    if (roomDown != nullptr) {
        Doors[3].GetRectangle()->x = 0;
        Doors[3].GetRectangle()->y = -2000;
        Doors[3].GetRectangle()->w = 50;
        Doors[3].GetRectangle()->h = 50;
        Doors[3].SetType(4);
    }
    if (roomUp != nullptr) {
        Doors[1].GetRectangle()->x = 0;
        Doors[1].GetRectangle()->y = 2000;
        Doors[1].GetRectangle()->w = 50;
        Doors[1].GetRectangle()->h = 50;
        Doors[1].SetType(2);
    }


    for ( auto &it:Floors)
    {
        if (roomLeft != nullptr) {
            if (it.GetRectangle()->x < Doors[0].GetRectangle()->x) {
                Doors[0].GetRectangle()->x = it.GetRectangle()->x;
                Doors[0].GetRectangle()->y = it.GetRectangle()->y;
            }
        }
        if (roomRight != nullptr) {
            if (it.GetRectangle()->x > Doors[2].GetRectangle()->x) {
                Doors[2].GetRectangle()->x = it.GetRectangle()->x;
                Doors[2].GetRectangle()->y = it.GetRectangle()->y;
            }
        }
        if (roomDown != nullptr) {
            if (it.GetRectangle()->y > Doors[3].GetRectangle()->y) {
                Doors[3].GetRectangle()->y = it.GetRectangle()->y;
                Doors[3].GetRectangle()->x = it.GetRectangle()->x;
            }
        }
        if (roomUp != nullptr) {
            if (it.GetRectangle()->y < Doors[1].GetRectangle()->y) {
                Doors[1].GetRectangle()->y = it.GetRectangle()->y;
                Doors[1].GetRectangle()->x = it.GetRectangle()->x;
            }
        }
    }
    if (roomLeft != nullptr) {
        //Doors[0].GetRectangle()->x = Floors[0].GetRectangle()->x;
        Doors[0].GetRectangle()->y += Floors[0].GetRectangle()->h / 2;
        std::cout << "MIN X: " << Doors[0].GetRectangle()->x << "\n";
    }

    if (roomRight != nullptr) {
        Doors[2].GetRectangle()->x += Floors[0].GetRectangle()->w - 50;
        Doors[2].GetRectangle()->y += Floors[0].GetRectangle()->h / 2;
        std::cout << "MAX X: " << Doors[2].GetRectangle()->x << "\n";
    }

    if (roomDown != nullptr) {
        Doors[3].GetRectangle()->y += Floors[0].GetRectangle()->h - 50;
        Doors[3].GetRectangle()->x += Floors[0].GetRectangle()->w / 2;
        std::cout << "MAX Y: " << Doors[3].GetRectangle()->y << "\n";
    }

    if (roomUp != nullptr) {
        //Doors[1].GetRectangle()->y = Floors[0].GetRectangle()->y;
        Doors[1].GetRectangle()->x += Floors[0].GetRectangle()->w / 2;
        std::cout << "MIN Y: " << Doors[1].GetRectangle()->y << "\n";
    }



}

void Map::CreateRooms(Room *&tempRoom) {
    if (startingRoom == nullptr) {
        tempRoom = new Room();
        startingRoom = tempRoom;
    }
    Rooms.push_back(tempRoom);
    tempRoom->SetTextureFloor(Textures[0].GetTexture());
    tempRoom->SetTextureWall(Textures[1].GetTexture());
    tempRoom->SetTextureDoor(Textures[2].GetTexture());

    Floor tempFloor;
    tempRoom->GetFloors().push_back(tempFloor);
    tempRoom->GetFloors().back().GetRectangle()->x = 200;
    tempRoom->GetFloors().back().GetRectangle()->y = 100;
    tempRoom->GetFloors().back().GetRectangle()->w = 1000;
    tempRoom->GetFloors().back().GetRectangle()->h = 600;
    int random = 0;
    Floor leftRect = tempRoom->GetFloors().back();
    Floor rightRect = tempRoom->GetFloors().back();
    Floor upperRect = tempRoom->GetFloors().back();
    Floor downRect = tempRoom->GetFloors().back();
    bool leftPossible = false;
    bool rightPossible = false;
    bool upperPossible = false;
    bool downPossible = false;
    while (roomMaxCount > 0)
    {
        random = rand() % 8 +1;
        int random2 = rand() % 4 + 1;
        if (tempRoom->roomLeft == nullptr && random == 1) {
            roomMaxCount--;
            if (leftPossible) {
                tempRoom->MoveRectangle(leftRect, 'r');
                tempRoom->GetFloors().push_back(leftRect);
            }
            else
            {
                leftRect.GetRectangle()->x -= 950;
                tempRoom->GetFloors().push_back(leftRect);
                leftPossible = true;
            }
        }
        else if(random == 5){
            if (tempRoom->roomLeft == nullptr) {
                roomMaxCount--;
                tempRoom->roomLeft = new Room();
                tempRoom->roomLeft->roomRight = tempRoom;
                CreateRooms(tempRoom->roomLeft);
                if (random2 == 1 && tempRoom->roomUp == nullptr) {
                    roomMaxCount--;
                    tempRoom->roomUp = new Room();
                    tempRoom->roomUp->roomDown = tempRoom;
                    CreateRooms(tempRoom->roomUp);
                }
            }

        }

        else if (tempRoom->roomUp == nullptr && random == 2) {
            roomMaxCount--;
            if (upperPossible) {
                tempRoom->MoveRectangle(upperRect, 'd');
                tempRoom->GetFloors().push_back(upperRect);
            }
            else
            {
                upperRect.GetRectangle()->y -= 550;
                tempRoom->GetFloors().push_back(upperRect);
                upperPossible = true;
            }
        }
        else if (random == 6) {
            if (tempRoom->roomUp == nullptr) {
                roomMaxCount--;
                tempRoom->roomUp = new Room();
                tempRoom->roomUp->roomDown = tempRoom;
                CreateRooms(tempRoom->roomUp);
                if (random2 == 2 && tempRoom->roomLeft == nullptr) {
                    roomMaxCount--;
                    tempRoom->roomLeft = new Room();
                    tempRoom->roomLeft->roomRight = tempRoom;
                    CreateRooms(tempRoom->roomLeft);
                }
            }
        }

        else if (tempRoom->roomRight == nullptr && random == 3) {
            roomMaxCount--;
            if (rightPossible) {
                tempRoom->MoveRectangle(rightRect, 'l');
                tempRoom->GetFloors().push_back(rightRect);
            }
            else
            {
                rightRect.GetRectangle()->x += 950;
                tempRoom->GetFloors().push_back(rightRect);
                rightPossible = true;
            }
        }
        else if (random == 7) {
            if (tempRoom->roomRight == nullptr) {
                roomMaxCount--;
                tempRoom->roomRight = new Room();
                tempRoom->roomRight->roomLeft = tempRoom;
                CreateRooms(tempRoom->roomRight);
                if (random2 == 3 && tempRoom->roomDown == nullptr) {
                    roomMaxCount--;
                    tempRoom->roomDown = new Room();
                    tempRoom->roomDown->roomUp = tempRoom;
                    CreateRooms(tempRoom->roomDown);
                }
            }

        }

        else if (tempRoom->roomDown == nullptr && random == 4) {
            roomMaxCount--;
            if (downPossible) {
                tempRoom->MoveRectangle(downRect, 'u');
                tempRoom->GetFloors().push_back(downRect);
            }
            else
            {
                downRect.GetRectangle()->y += 550;
                tempRoom->GetFloors().push_back(downRect);
                downPossible = true;
            }
        }
        else if (random == 8) {
            if (tempRoom->roomDown == nullptr) {
                roomMaxCount--;
                tempRoom->roomDown = new Room();
                tempRoom->roomDown->roomUp = tempRoom;
                CreateRooms(tempRoom->roomDown);
                if (random2 == 1 && tempRoom->roomRight == nullptr) {
                    roomMaxCount--;
                    tempRoom->roomRight = new Room();
                    tempRoom->roomRight->roomLeft = tempRoom;
                    CreateRooms(tempRoom->roomRight);
                }
            }

        }

    }
    tempRoom->CreateWalls();
    tempRoom->DeleteRectangles();
    tempRoom->DeleteWalls();
    tempRoom->LocateDoorPositions();
    
}

void Map::CreateLevel() {
    CreateRooms(startingRoom);
    currentRoom = startingRoom;
    std::cout <<"ROOM COUNT: " << Rooms.size() << "\n";
}

void Map::CheckCollision(Player *player) {
    currentRoom->CheckCollision(player);
    switch (currentRoom->CheckCollisionDoors(player))
    {
        case 1:
            currentRoom = currentRoom->roomLeft;
            for (auto& it : currentRoom->GetDoors()) {
                if (it.GetType() == 3) {
                    player->GetRectangle()->x = it.GetRectangle()->x - 100;
                    player->GetRectangle()->y = it.GetRectangle()->y;
                }
            }
            std::cout << currentRoom->GetDoors().size()<<"\n";
            break;
        case 2:
            currentRoom = currentRoom->roomUp;
            for (auto& it : currentRoom->GetDoors()) {
                if (it.GetType() == 4) {
                    player->GetRectangle()->x = it.GetRectangle()->x;
                    player->GetRectangle()->y = it.GetRectangle()->y -100;
                }
            }
            std::cout << currentRoom->GetDoors().size() << "\n";
            break;
        case 3:
            currentRoom = currentRoom->roomRight;
            for (auto& it : currentRoom->GetDoors()) {
                if (it.GetType() == 1) {
                    player->GetRectangle()->x = it.GetRectangle()->x +100;
                    player->GetRectangle()->y = it.GetRectangle()->y;
                }
            }
            break;
        case 4:
            currentRoom = currentRoom->roomDown;
            for (auto& it : currentRoom->GetDoors()) {
                if (it.GetType() == 2) {
                    player->GetRectangle()->x = it.GetRectangle()->x;
                    player->GetRectangle()->y = it.GetRectangle()->y + 100;
                }
            }
            break;
    }
}

Map::~Map() {
    for (auto& it : Textures) {
        SDL_DestroyTexture(it.GetTexture());
    }
}
