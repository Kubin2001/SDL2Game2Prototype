#include <iostream>
#include <SDL.h>

#include <filesystem>
#include <vector>
#include "TextureManager.h"

SDL_Texture* Texture::GetTexture() { return texture; }

void Texture::SetTexture(SDL_Texture* temptex) { texture = temptex; }

std::string Texture::GetName() { return name; }

void Texture::SetName(std::string temp) { name = temp; }


SDL_Texture* load(const char* file, SDL_Renderer* ren) {
	SDL_Surface* tmpSurface = IMG_Load(file);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return tex;
}



void LoadMultipleTextures(std::vector<Texture>& vector, const std::string& directory, SDL_Renderer* renderer){
    Texture temp;
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".png") {
            std::string pathString = entry.path().string();
            const char* path = pathString.c_str();
            vector.push_back(temp);
            vector.back().SetTexture(load(path, renderer));
            SDL_Texture* texture = vector.back().GetTexture();
            std::string name = entry.path().stem().string();
            vector.back().SetName(name);
        }
    }
}

