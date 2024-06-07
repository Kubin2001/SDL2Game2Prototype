#include <iostream>
#include <SDL.h>
#include "Player.h"

extern long long int framesCounter;

Player::Player(SDL_Renderer * renderer) {
    this->renderer = renderer;
}

SDL_Rect* Player::GetRectangle() {
    return &rectangle;
}

SDL_Texture* Player::GetTexture() {
    return texture;
}

void Player::SetTexture(SDL_Texture * temptex) {
    texture = temptex;
}

void Player::SetCollision(int index, bool value) {
    CollsionSides[index] = value;
}

void Player::Render(SDL_Rect &camRect) {
    SDL_Rect temp;
    temp.x = GetRectangle()->x - camRect.x;
    temp.y = GetRectangle()->y - camRect.y;
    temp.w = GetRectangle()->w;
    temp.h = GetRectangle()->h;
    SDL_RenderCopy(renderer, texture, NULL, &temp);
}

void Player::Movement(const Uint8* state) {
    bool combined = false;
    if (state[SDL_SCANCODE_RIGHT] && !CollsionSides[2]) {
        combined = true;
        GetRectangle()->x+= moveSpeed;
    }
    if (state[SDL_SCANCODE_LEFT] && !CollsionSides[0])
    {
        combined = true;
        GetRectangle()->x-= moveSpeed;
    }
    if (state[SDL_SCANCODE_DOWN] && !CollsionSides[1])
    {
        if (combined) {
            GetRectangle()->y += moveSpeed/2;
        }
        else
        {
            GetRectangle()->y += moveSpeed;
        }
    }
    if (state[SDL_SCANCODE_UP] && !CollsionSides[3])
    {
        if (combined) {
            GetRectangle()->y -= moveSpeed / 2;
        }
        else
        {
            GetRectangle()->y -= moveSpeed;
        }
    }
}

Player::~Player() {
    SDL_DestroyTexture(texture);
}

