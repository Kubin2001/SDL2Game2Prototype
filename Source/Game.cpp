#include <SDL.h>
#include <iostream>
#include "SDL_image.h"
#include "TextureManager.h"

#include "Game.h"

extern int windowWidth;
extern int windowHeight;
extern long long int framesCounter;
extern bool status;

Game::Game() {
    window = nullptr;
    renderer = nullptr;
    player = nullptr;
    camera = nullptr;
    map = nullptr;
    ui = nullptr;
}

void Game::Start() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("NotIssac", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    player = std::make_unique<Player>(renderer);
    camera = std::make_unique<Camera>();
    map = std::make_unique<Map>(renderer);
    ui = std::make_unique<UI>(renderer);
    TextureManager::Start(renderer);
    LoadTextures();
    map->CreateLevel(ui.get());


}

void Game::LoadTextures() {
    player->SetTexture(TextureManager::LoadSingleTexture("textures/player.png"));
    map->LoadTextures();
    ui->LoadTextures();
}

void Game::Events() {
    framesCounter++;
    player->SetCollision(0, 0);
    player->SetCollision(1, 0);
    player->SetCollision(2, 0);
    player->SetCollision(3, 0);
    map->CheckCollision(player.get());
    camera->UpdatePosition(*player->GetRectangle());
    while (SDL_PollEvent(&event)) {
        ui->OpenMap(event);
        Exit();
    }
}

void Game::Exit() {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
            status = false;
        }
    }
}

void Game::Movement(bool &status) {
    SDL_PumpEvents();
    const Uint8* state = SDL_GetKeyboardState(NULL);
    player->Movement(state);
}

void Game::Render() {
    SDL_RenderClear(renderer);
    map->Render(*camera->GetRectangle());
    player->Render(*camera->GetRectangle());
    ui->Render();
    SDL_RenderPresent(renderer);
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    //std::cout << "Resources Destroyed";
}
