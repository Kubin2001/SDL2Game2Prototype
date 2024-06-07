#include <iostream>
#include <SDL.h>
#include "Camera.h"

Camera::Camera() {
}



SDL_Rect* Camera::GetRectangle() {
    return &rectangle;
}


void Camera::UpdatePosition(const SDL_Rect playerRect) {
    rectangle.x = playerRect.x + playerRect.w / 2 - rectangle.w / 2;
    rectangle.y = playerRect.y + playerRect.h / 2 - rectangle.h / 2;
}


Camera::~Camera() {
}

