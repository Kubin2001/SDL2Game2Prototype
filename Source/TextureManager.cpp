#include <iostream>
#include <SDL.h>

#include <filesystem>
#include <vector>
#include "TextureManager.h"

std::unordered_map<std::string, SDL_Texture*> TextureManager::Textures;
SDL_Renderer* TextureManager::renderer = nullptr;


void TextureManager::Start(SDL_Renderer *ren) {
   renderer = ren;
}


void TextureManager::LoadSingleTexture(const char* filePath, const std::string& name) {
	SDL_Surface* tmpSurface = IMG_Load(filePath);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
    Textures.insert(std::make_pair(name, tex));
}



void TextureManager::LoadMultipleTextures(const std::string& directory){
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".png") {
            std::string pathString = entry.path().string();
            const char* path = pathString.c_str();
            std::string name = entry.path().stem().string();
            LoadSingleTexture(path, name);
        }
    }
}


SDL_Texture* TextureManager::GetTextureByName(const std::string& name) {
    auto it = Textures.find(name);
    if (it != Textures.end()) {
        return it->second;
    }
    std::cerr << "Texture not found: " << name << "\n";
    return nullptr;
}

bool TextureManager::DeleteTexture(const std::string& name) {
    auto it = Textures.find(name);
    if (it != Textures.end()) {
        SDL_DestroyTexture(it->second);
        Textures.erase(it);
        return true;
    }
    else
    {
        return false;
    }
}

void TextureManager::Clear() {
    for (auto& pair : Textures) {
        SDL_DestroyTexture(pair.second);
    }
}
