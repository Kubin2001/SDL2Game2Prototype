#pragma once
#include <SDL.h>
#include <memory>
#include "Player.h"
#include "Camera.h"
#include "Map.h"
#include "UI.h"

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::unique_ptr<Player> player;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Map> map;
    std::unique_ptr<UI> ui;
    SDL_Event event = {};



public:
    Game();

    void Start();

    void LoadTextures();

    void Events();

    void Exit();

    void Movement(bool& status);

    void Render();

    ~Game();
};
