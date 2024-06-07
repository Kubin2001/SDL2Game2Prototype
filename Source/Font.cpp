#include <iostream>
#include <SDL.h>
#include "Font.h"

Font::Font() {

}

SDL_Texture* Font::GetTexture() {
    return texture;
}

int Font::GetSize() {
    return size;
}

void Font::SetSize(int temp) {
    size = temp;
}

void Font::SetTexture(SDL_Texture* temptex) {
    texture = temptex;
}

SDL_Rect* Font::GetRectangle() {
    return &rectangle;
}

void Font::LoadText(int stepW,int stepH) {
    SDL_Rect temp;
    int xCord = 1;
    int yCord = 1;
    for (int i = 0; i < size; i++)
    {
        sourceRectangles.push_back(temp);
        sourceRectangles[i].x = xCord;
        sourceRectangles[i].y = yCord;
        sourceRectangles[i].w = stepW;
        sourceRectangles[i].h = stepH;
        xCord += 31;
    }
}

void Font::RenderText(SDL_Renderer* renderer, std::string text, int x, int y, int w, int h, int step) {
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
    int temp = rectangle.x;
    for (int i = 0; i < text.length(); i++)
    {
        switch (text[i])
        {
        case 'A':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[0], &rectangle);
            break;
        case 'B':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[1], &rectangle);
            break;
        case 'C':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[2], &rectangle);
            break;
        case 'D':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[3], &rectangle);
            break;
        case 'E':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[4], &rectangle);
            break;
        case 'F':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[5], &rectangle);
            break;
        case 'G':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[6], &rectangle);
            break;
        case 'H':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[7], &rectangle);
            break;
        case 'I':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[8], &rectangle);
            break;
        case 'J':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[9], &rectangle);
            break;
        case 'K':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[10], &rectangle);
            break;
        case 'L':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[11], &rectangle);
            break;
        case 'M':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[12], &rectangle);
            break;
        case 'N':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[13], &rectangle);
            break;
        case 'O':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[14], &rectangle);
            break;
        case 'P':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[15], &rectangle);
            break;
        case 'Q':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[16], &rectangle);
            break;
        case 'R':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[17], &rectangle);
            break;
        case 'S':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[18], &rectangle);
            break;
        case 'T':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[19], &rectangle);
            break;
        case 'U':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[20], &rectangle);
            break;
        case 'V':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[21], &rectangle);
            break;
        case 'W':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[22], &rectangle);
            break;
        case 'X':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[23], &rectangle);
            break;
        case 'Y':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[24], &rectangle);
            break;
        case 'Z':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[25], &rectangle);
            break;
        case 'a':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[26], &rectangle);
            break;
        case 'b':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[27], &rectangle);
            break;
        case 'c':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[28], &rectangle);
            break;
        case 'd':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[29], &rectangle);
            break;
        case 'e':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[30], &rectangle);
            break;
        case 'f':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[31], &rectangle);
            break;
        case 'g':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[32], &rectangle);
            break;
        case 'h':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[33], &rectangle);
            break;
        case 'i':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[34], &rectangle);
            break;
        case 'j':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[35], &rectangle);
            break;
        case 'k':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[36], &rectangle);
            break;
        case 'l':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[37], &rectangle);
            break;
        case 'm':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[38], &rectangle);
            break;
        case 'n':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[39], &rectangle);
            break;
        case 'o':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[40], &rectangle);
            break;
        case 'p':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[41], &rectangle);
            break;
        case 'q':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[42], &rectangle);
            break;
        case 'r':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[43], &rectangle);
            break;
        case 's':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[44], &rectangle);
            break;
        case 't':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[45], &rectangle);
            break;
        case 'u':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[46], &rectangle);
            break;
        case 'v':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[47], &rectangle);
            break;
        case 'w':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[48], &rectangle);
            break;
        case 'x':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[49], &rectangle);
            break;
        case 'y':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[50], &rectangle);
            break;
        case 'z':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[51], &rectangle);
            break;
        case '0':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[52], &rectangle);
            break;
        case '1':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[53], &rectangle);
            break;
        case '2':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[54], &rectangle);
            break;
        case '3':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[55], &rectangle);
            break;
        case '4':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[56], &rectangle);
            break;
        case '5':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[57], &rectangle);
            break;
        case '6':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[58], &rectangle);
            break;
        case '7':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[59], &rectangle);
            break;
        case '8':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[60], &rectangle);
            break;
        case '9':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[61], &rectangle);
            break;
        case ':':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[62], &rectangle);
            break;
        case '.':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[63], &rectangle);
            break;
        case '-':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[64], &rectangle);
            break;
        case '+':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[65], &rectangle);
            break;
        case '(':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[66], &rectangle);
            break;
        case ')':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[67], &rectangle);
            break;
        case '/':
            rectangle.y += step;
            rectangle.x = x - step;
            break;
           
        default:
            break;
        }
        rectangle.x += step;
    }
    rectangle.x = temp;
}

Font::~Font() {
    SDL_DestroyTexture(texture);
}