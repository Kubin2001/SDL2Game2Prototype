#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "SDL_image.h"



class TextureManager {
	private:
		static std::unordered_map<std::string, SDL_Texture *> Textures;
		static SDL_Renderer* renderer;

	public:
		
		static void Start(SDL_Renderer* ren);
		
		static SDL_Texture* LoadSingleTexture(const char* file);


		static void LoadMultipleTextures(const std::string& directory);

		static SDL_Texture* GetTextureByName(const std::string& name);

		static bool DeleteTexture(const std::string & name);

		static void Clear();
		


};
