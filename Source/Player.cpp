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
    if (!state[SDL_SCANCODE_RIGHT] && !state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_UP] && !state[SDL_SCANCODE_DOWN]) {
        return;
    }

    if (state[SDL_SCANCODE_RIGHT] && !CollsionSides[2]) {
        if (state[SDL_SCANCODE_UP] && !CollsionSides[3]) {
            GetRectangle()->x += (moveSpeed / 2) + 1;
            GetRectangle()->y -= (moveSpeed / 2) + 1;
        }
        else if (state[SDL_SCANCODE_DOWN] && !CollsionSides[1]) {
            GetRectangle()->x += (moveSpeed / 2) + 1;
            GetRectangle()->y += (moveSpeed / 2) + 1;
        }
        else
        {
            GetRectangle()->x += moveSpeed;
        }
    }
    else if (state[SDL_SCANCODE_LEFT] && !CollsionSides[0]) {
        if (state[SDL_SCANCODE_UP] && !CollsionSides[3]) {
            GetRectangle()->x -= (moveSpeed / 2) + 1;
            GetRectangle()->y -= (moveSpeed / 2) + 1;
        }
        else if (state[SDL_SCANCODE_DOWN] && !CollsionSides[1]) {
            GetRectangle()->x -= (moveSpeed / 2) + 1;
            GetRectangle()->y += (moveSpeed / 2) + 1;
        }
        else
        {
            GetRectangle()->x -= moveSpeed;
        }
    }
    else if (state[SDL_SCANCODE_DOWN] && !CollsionSides[1]) {

        if (state[SDL_SCANCODE_LEFT] && !CollsionSides[0]) {
            GetRectangle()->x -= (moveSpeed / 2) + 1;
            GetRectangle()->y += (moveSpeed / 2) + 1;
        }
        else if (state[SDL_SCANCODE_RIGHT] && !CollsionSides[2]) {
            GetRectangle()->x += (moveSpeed / 2) + 1;
            GetRectangle()->y += (moveSpeed / 2) + 1;
        }
        else
        {
            GetRectangle()->y += moveSpeed;
        }
    }
    else if (state[SDL_SCANCODE_UP] && !CollsionSides[3]) {
        if (state[SDL_SCANCODE_LEFT] && !CollsionSides[0]) {
            GetRectangle()->x -= (moveSpeed / 2) + 1;
            GetRectangle()->y -= (moveSpeed / 2) + 1;
        }
        else if (state[SDL_SCANCODE_RIGHT] && !CollsionSides[2]) {
            GetRectangle()->x += (moveSpeed / 2) + 1;
            GetRectangle()->y -= (moveSpeed / 2) + 1;
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

