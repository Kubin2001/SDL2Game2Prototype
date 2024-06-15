#include <SDL.h>
#include <iostream>
#include "SDL_image.h"
#include "TextureManager.h"

#include "Game.h"

extern int windowWidth;
extern int windowHeight;
extern long long int framesCounter;

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
    LoadTextures();
    map->CreateLevel();


}

void Game::LoadTextures() {
    player->SetTexture(load("textures/player.png", renderer));
    map->LoadTextures();
}

void Game::Events() {
    framesCounter++;
    player->SetCollision(0, 0);
    player->SetCollision(1, 0);
    player->SetCollision(2, 0);
    player->SetCollision(3, 0);
    map->CheckCollision(player.get());
    camera->UpdatePosition(*player->GetRectangle());
}

void Game::Exit(bool& status, const Uint8* state) {
    if (state[SDL_SCANCODE_ESCAPE]) {
        status = false;
    }
}

void Game::Movement(bool &status) {
    SDL_PumpEvents();
    const Uint8* state = SDL_GetKeyboardState(NULL);
    player->Movement(state);
    Exit(status,state);
}

void Game::Render() {
    SDL_RenderClear(renderer);
    map->Render(*camera->GetRectangle());
    player->Render(*camera->GetRectangle());
    SDL_RenderPresent(renderer);
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    //std::cout << "Resources Destroyed";
}
