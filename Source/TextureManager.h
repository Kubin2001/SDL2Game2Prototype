#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "SDL_image.h"



class TextureManager {
	private:
		std::unordered_map<std::string, SDL_Texture *> Textures;
		SDL_Renderer* renderer = nullptr;

	public:
		
		TextureManager(SDL_Renderer* renderer);
		
		SDL_Texture* LoadSingleTexture(const char* file);


		void LoadMultipleTextures(const std::string& directory);

		SDL_Texture* GetTextureByName(const std::string& name);

		bool DeleteTexture(const std::string & name);
		
		~TextureManager();


};
